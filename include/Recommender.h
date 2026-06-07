#pragma once

#include "MovieManager.h"
#include "RatingManager.h"
#include "SimilarityCalculator.h"
#include "Constants.h"
#include <vector>
#include <utility>

class Recommender {
private:
    MovieManager& movieManager;
    RatingManager& ratingManager;

    std::vector<std::pair<int, double>> findSupportUsersForMovie(
        int targetUserId,
        int movieId,
        int k = AppConstants::DEFAULT_SIMILAR_USER_COUNT
    ) const;

public:
    Recommender(MovieManager& movieMgr, RatingManager& ratingMgr);

    std::vector<std::pair<int, double>> getAllSimilarities(
        int targetUserId
    ) const;

    std::vector<std::pair<int, double>> findSimilarUsers(
        int targetUserId,
        int k = AppConstants::DEFAULT_SIMILAR_USER_COUNT
    ) const;

    std::vector<int> recommend(
        int targetUserId,
        int k = AppConstants::DEFAULT_SIMILAR_USER_COUNT,
        int n = AppConstants::DEFAULT_RECOMMENDATION_COUNT
    ) const;

    void printSimilarityReport(
        int targetUserId
    ) const;

    void printRecommendations(
        int targetUserId,
        int k = AppConstants::DEFAULT_SIMILAR_USER_COUNT,
        int n = AppConstants::DEFAULT_RECOMMENDATION_COUNT
    ) const;
};