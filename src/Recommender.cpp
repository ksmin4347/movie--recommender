#include "Recommender.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <iomanip>
#include <cmath>

Recommender::Recommender(MovieManager& movieMgr, RatingManager& ratingMgr)
    : movieManager(movieMgr), ratingManager(ratingMgr) {}   //데이터 복사할 필요 없어서 기존 manager를 참조로 연결

std::vector<std::pair<int, double>> Recommender::getAllSimilarities(    //기존 사용자와 다른 모든 사용자의 유사도 계산
    int targetUserId
) const {
    std::vector<std::pair<int, double>> similarities;           //<사용자 id, 유사도>를 저장할 벡터

    std::vector<Rating> targetRatings = ratingManager.findByUser(targetUserId); //기준 사용자의 평점 목록 가져오기

    if (targetRatings.empty()) {        //비었으면 빈 벡터 반환
        return similarities;
    }

    std::vector<int> allUserIds = ratingManager.getAllUserIds();        //평점을 남긴 모든 사용자 id를 가져오기

    for (int otherUserId : allUserIds) {    //자기 자신은 패스
        if (otherUserId == targetUserId) {
            continue;
        }

        std::vector<Rating> otherRatings = ratingManager.findByUser(otherUserId);       //비교 대상자 평점 목록

        double similarity = SimilarityCalculator::calculate(    //유사도 계산 후 벡터에 넣음
            targetRatings,
            otherRatings
        );

        similarities.push_back({otherUserId, similarity});
    }

    std::sort(similarities.begin(), similarities.end(),             //유사도 높은 순으로 정렬
        [](const std::pair<int, double>& a,
           const std::pair<int, double>& b) {
            if (std::abs(a.second - b.second) < 0.000001) {
                return a.first < b.first;
            }

            return a.second > b.second;
        }
    );

    return similarities;
}

std::vector<std::pair<int, double>> Recommender::findSimilarUsers(      //기준 사용자와 비슷한 사용자 상위 k명 고름
    int targetUserId,
    int k
) const {
    std::vector<std::pair<int, double>> allSimilarities =       //전체 유사도 목록 가져오기
        getAllSimilarities(targetUserId);

    std::vector<std::pair<int, double>> positiveSimilarities;   

    if (k <= 0) {
        return positiveSimilarities;        
    }

    for (const auto& item : allSimilarities) {          //유사도가 양수인 사용자만 따로 저장
        if (item.second > 0.0) {                    //item.second: 유사도
            positiveSimilarities.push_back(item);
        }
    }

    if (positiveSimilarities.empty()) {     //바슷한 사용자 없으면 빈 결과 반환
        return positiveSimilarities;
    }

    if (static_cast<int>(positiveSimilarities.size()) <= k) {       //엣지 케이스 처리(k보다 작은 비슷한 사용자면 그냥 반환)
        return positiveSimilarities;
    }

    double cutoff = positiveSimilarities[k - 1].second;         //상위 k명의 마지막 점수를 기준점으로 잡음
    std::vector<std::pair<int, double>> selected;

    for (const auto& item : positiveSimilarities) {         //그 사람의 마지막 점수보다 큰거만 저장
        if (item.second + 0.000001 >= cutoff) {
            selected.push_back(item);
        }
    }

    return selected;
}

std::vector<int> Recommender::recommend(    //사용자 기반 추천 영화 id 목록 반환
    int targetUserId,
    int k,  //유사 사용자 몇 명 참고할지
    int n
) const {
    std::vector<int> result;

    if (k <= 0 || n <= 0) {     
        return result;
    }

    std::vector<Rating> targetRatings = ratingManager.findByUser(targetUserId); //추천 받을 사용자 평점 목록

    if (targetRatings.empty()) {        
        return result;
    }

    std::set<int> watchedMovieIds;          //사용자가 이미 본 영화 id 저장

    for (const Rating& rating : targetRatings) {        //이미 본 영화를 set에 저장
        watchedMovieIds.insert(rating.getMovieId());
    }

    std::vector<std::pair<int, double>> similarUsers =      //유사도 상위 k명 찾기
        findSimilarUsers(targetUserId, k);

    if (similarUsers.empty()) {
        return result;
    }

    std::map<int, double> weightedScoreSum;            //해당 영화 유사도*평점 합
    std::map<int, double> weightSum;                   //해당 영화에 반영된 유사도 합

    for (const auto& userSimilarity : similarUsers) {   //유사 사용자들 하나씩 봄
        int otherUserId = userSimilarity.first;         //사용자 아이디 저장
        double similarity = userSimilarity.second;      //유사도 저장

        std::vector<Rating> otherRatings =
            ratingManager.findByUser(otherUserId);      //유저 사용자가 남긴 평점 목록 가져오기

        for (const Rating& rating : otherRatings) {     //평점 하나씩 본 후 현재 영화 id와 점수 꺼냄
            int movieId = rating.getMovieId();
            double score = rating.getScore();

            if (score < 4.0) {
                continue;
            }

            if (watchedMovieIds.find(movieId) != watchedMovieIds.end()) {       //이미 본건 패스
                continue;
            }

            weightedScoreSum[movieId] += similarity * score;        //추천 점수 계산 위해 누적
            weightSum[movieId] += similarity;
        }
    }

    std::vector<std::pair<int, double>> scoredMovies;           //최종 추천 점수 저장할 벡터

    for (const auto& item : weightedScoreSum) {         //후보 영화 하나씩 보면서 점수 계산 
        int movieId = item.first;

        if (weightSum[movieId] == 0.0) {
            continue;
        }

        double finalScore = weightedScoreSum[movieId] / weightSum[movieId];     //가중 평균 계산

        scoredMovies.push_back({movieId, finalScore});
    }

    std::sort(scoredMovies.begin(), scoredMovies.end(),
        [](const std::pair<int, double>& a,
           const std::pair<int, double>& b) {
            if (std::abs(a.second - b.second) < 0.000001) {
                return a.first < b.first;
            }

            return a.second > b.second;
        }
    );

    int count = std::min(n, static_cast<int>(scoredMovies.size()));     //n개보다 적을 때 대비

    for (int i = 0; i < count; i++) {
        result.push_back(scoredMovies[i].first);
    }

    return result;
}

void Recommender::printSimilarityReport(        //10번 메뉴에서 사용
    int targetUserId
) const {
    std::vector<Rating> targetRatings = ratingManager.findByUser(targetUserId);     //기준 사용자 평점 가져오기

    if (targetRatings.empty()) {
        std::cout << "해당 사용자의 평점 데이터가 없습니다." << std::endl;
        return;
    }

    std::vector<std::pair<int, double>> similarities =      //전체 유사도 계산
        getAllSimilarities(targetUserId);

    if (similarities.empty()) {
        std::cout << "비교할 다른 사용자가 없습니다." << std::endl;
        return;
    }

    std::cout << std::fixed << std::setprecision(1);
    std::cout << "\n--- 유사도 계산 결과 ---" << std::endl;

    for (const auto& item : similarities) {     //모든 사용자와의 유사도 출력
        std::cout << "사용자 " << targetUserId
                  << " ↔ 사용자 " << item.first
                  << " 유사도: " << item.second
                  << std::endl;
    }

    double bestSimilarity = similarities[0].second;         //정렬 되있으므로 첫번째가 가장 높은 유사도

    if (bestSimilarity <= -100.0) {
        std::cout << "비교 가능한 유사 사용자가 없습니다." << std::endl;
        return;
    }

    std::cout << "\n가장 비슷한 사용자:" << std::endl;

    for (const auto& item : similarities) {             //최고 유사도와 같은 사람을 모두 출력
        if (std::abs(item.second - bestSimilarity) < 0.000001) {    //abs쓰는 이유: 소수라서 아주 작은 오차 생길 수 있음
            std::cout << "사용자 " << item.first
                      << " (유사도 " << item.second << ")"
                      << std::endl;
        }
    }
}

void Recommender::printRecommendations( //11번 메뉴 사용자 추천 출력에 사용
    int targetUserId,
    int k,
    int n
) const {
    std::vector<Rating> targetRatings = ratingManager.findByUser(targetUserId);     //기준 사용자 평점 가져오기

    if (targetRatings.empty()) {
        std::cout << "해당 사용자의 평점 데이터가 없어 추천할 수 없습니다." << std::endl;
        return;
    }

    std::vector<int> recommendations = recommend(targetUserId, k, n);       //실제 추천 계산

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