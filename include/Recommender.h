#pragma once

#include "MovieManager.h"
#include "RatingManager.h"
#include "SimilarityCalculator.h"
#include <vector>
#include <utility>

class Recommender {
private:
    MovieManager& movieManager;
    RatingManager& ratingManager;

public:
    Recommender(MovieManager& movieMgr, RatingManager& ratingMgr);

    std::vector<std::pair<int, double>> getAllSimilarities(
        int targetUserId
    ) const;

    std::vector<std::pair<int, double>> findSimilarUsers(
        int targetUserId,
        int k = 3
    ) const;

    std::vector<int> recommend(
        int targetUserId,
        int k = 3,
        int n = 5
    ) const;

    void printSimilarityReport(
        int targetUserId
    ) const;

    void printRecommendations(
        int targetUserId,
        int k = 3,
        int n = 5
    ) const;
};