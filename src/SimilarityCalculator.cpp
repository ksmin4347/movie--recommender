#include "SimilarityCalculator.h"
#include "Constants.h"
#include <cmath>

double SimilarityCalculator::calculate(
    const std::vector<Rating>& user1,
    const std::vector<Rating>& user2)
{
    int commonCount = 0;
    double scoreDiffSum = 0.0;

    for (const Rating& r1 : user1) {
        for (const Rating& r2 : user2) {
            if (r1.getMovieId() == r2.getMovieId()) {
                commonCount++;
                scoreDiffSum += std::abs(r1.getScore() - r2.getScore());
            }
        }
    }

    if (commonCount == 0) {
        return AppConstants::NO_COMMON_MOVIE_SIMILARITY;
    }

    return commonCount * AppConstants::SIMILARITY_COMMON_MOVIE_WEIGHT
           - scoreDiffSum;
}