#include "Recommender.h"
#include "Constants.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <iomanip>
#include <cmath>

Recommender::Recommender(MovieManager& movieMgr, RatingManager& ratingMgr)
    : movieManager(movieMgr), ratingManager(ratingMgr) {}

std::vector<std::pair<int, double>> Recommender::getAllSimilarities(
    int targetUserId
) const {
    std::vector<std::pair<int, double>> similarities;

    std::vector<Rating> targetRatings = ratingManager.findByUser(targetUserId);

    if (targetRatings.empty()) {
        return similarities;
    }

    std::vector<int> allUserIds = ratingManager.getAllUserIds();

    for (int otherUserId : allUserIds) {
        if (otherUserId == targetUserId) {
            continue;
        }

        std::vector<Rating> otherRatings = ratingManager.findByUser(otherUserId);

        double similarity = SimilarityCalculator::calculate(
            targetRatings,
            otherRatings
        );

        similarities.push_back({otherUserId, similarity});
    }

    std::sort(similarities.begin(), similarities.end(),
        [](const std::pair<int, double>& a,
           const std::pair<int, double>& b) {
            if (std::abs(a.second - b.second) < AppConstants::EPSILON) {
                return a.first < b.first;
            }

            return a.second > b.second;
        }
    );

    return similarities;
}

std::vector<std::pair<int, double>> Recommender::findSimilarUsers(
    int targetUserId,
    int k
) const {
    std::vector<std::pair<int, double>> allSimilarities =
        getAllSimilarities(targetUserId);

    std::vector<std::pair<int, double>> positiveSimilarities;

    if (k <= 0) {
        return positiveSimilarities;
    }

    for (const auto& item : allSimilarities) {
        if (item.second > AppConstants::MIN_RATING) {
            positiveSimilarities.push_back(item);
        }
    }

    if (positiveSimilarities.empty()) {
        return positiveSimilarities;
    }

    if (static_cast<int>(positiveSimilarities.size()) <= k) {
        return positiveSimilarities;
    }

    double cutoff = positiveSimilarities[k - 1].second;
    std::vector<std::pair<int, double>> selected;

    for (const auto& item : positiveSimilarities) {
        if (item.second + AppConstants::EPSILON >= cutoff) {
            selected.push_back(item);
        }
    }

    return selected;
}

std::vector<int> Recommender::recommend(
    int targetUserId,
    int k,
    int n
) const {
    std::vector<int> result;

    if (k <= 0 || n <= 0) {
        return result;
    }

    std::vector<Rating> targetRatings = ratingManager.findByUser(targetUserId);

    if (targetRatings.empty()) {
        return result;
    }

    std::set<int> watchedMovieIds;

    for (const Rating& rating : targetRatings) {
        watchedMovieIds.insert(rating.getMovieId());
    }

    std::vector<std::pair<int, double>> similarUsers =
        findSimilarUsers(targetUserId, k);

    if (similarUsers.empty()) {
        return result;
    }

    std::map<int, double> weightedScoreSum;
    std::map<int, double> weightSum;

    for (const auto& userSimilarity : similarUsers) {
        int otherUserId = userSimilarity.first;
        double similarity = userSimilarity.second;

        std::vector<Rating> otherRatings =
            ratingManager.findByUser(otherUserId);

        for (const Rating& rating : otherRatings) {
            int movieId = rating.getMovieId();
            double score = rating.getScore();

            if (score < AppConstants::HIGH_RATING_THRESHOLD) {
                continue;
            }

            if (watchedMovieIds.find(movieId) != watchedMovieIds.end()) {
                continue;
            }

            weightedScoreSum[movieId] += similarity * score;
            weightSum[movieId] += similarity;
        }
    }

    std::vector<std::pair<int, double>> scoredMovies;

    for (const auto& item : weightedScoreSum) {
        int movieId = item.first;

        if (weightSum[movieId] == AppConstants::MIN_RATING) {
            continue;
        }

        double finalScore = weightedScoreSum[movieId] / weightSum[movieId];

        scoredMovies.push_back({movieId, finalScore});
    }

    std::sort(scoredMovies.begin(), scoredMovies.end(),
        [](const std::pair<int, double>& a,
           const std::pair<int, double>& b) {
            if (std::abs(a.second - b.second) < AppConstants::EPSILON) {
                return a.first < b.first;
            }

            return a.second > b.second;
        }
    );

    int count = std::min(n, static_cast<int>(scoredMovies.size()));

    for (int i = 0; i < count; i++) {
        result.push_back(scoredMovies[i].first);
    }

    return result;
}

void Recommender::printSimilarityReport(
    int targetUserId
) const {
    std::vector<Rating> targetRatings = ratingManager.findByUser(targetUserId);

    if (targetRatings.empty()) {
        std::cout << "해당 사용자의 평점 데이터가 없습니다." << std::endl;
        return;
    }

    std::vector<std::pair<int, double>> similarities =
        getAllSimilarities(targetUserId);

    if (similarities.empty()) {
        std::cout << "비교할 다른 사용자가 없습니다." << std::endl;
        return;
    }

    std::cout << std::fixed
              << std::setprecision(AppConstants::OUTPUT_PRECISION);

    std::cout << "\n--- 유사도 계산 결과 ---" << std::endl;

    for (const auto& item : similarities) {
        std::cout << "사용자 " << targetUserId
                  << " ↔ 사용자 " << item.first
                  << " 유사도: " << item.second
                  << std::endl;
    }

    double bestSimilarity = similarities[0].second;

    if (bestSimilarity <= AppConstants::NO_COMMON_MOVIE_SIMILARITY) {
        std::cout << "비교 가능한 유사 사용자가 없습니다." << std::endl;
        return;
    }

    std::cout << "\n가장 비슷한 사용자:" << std::endl;

    for (const auto& item : similarities) {
        if (std::abs(item.second - bestSimilarity) < AppConstants::EPSILON) {
            std::cout << "사용자 " << item.first
                      << " (유사도 " << item.second << ")"
                      << std::endl;
        }
    }
}

void Recommender::printRecommendations(
    int targetUserId,
    int k,
    int n
) const {
    std::vector<Rating> targetRatings = ratingManager.findByUser(targetUserId);

    if (targetRatings.empty()) {
        std::cout << "해당 사용자의 평점 데이터가 없어 추천할 수 없습니다."
                  << std::endl;
        return;
    }

    std::vector<int> recommendations = recommend(targetUserId, k, n);

    if (recommendations.empty()) {
        std::cout << "추천할 영화가 없습니다." << std::endl;
        return;
    }

    std::cout << "\n=== 추천 영화 TOP " << n << " ===" << std::endl;

    int rank = 1;

    for (int movieId : recommendations) {
        const Movie* movie = movieManager.findById(movieId);

        if (movie != nullptr) {
            std::cout << rank << ". " << *movie << std::endl;
        } else {
            std::cout << rank << ". 영화 ID " << movieId << std::endl;
        }

        rank++;
    }
}