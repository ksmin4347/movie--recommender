#include "RatingManager.h"
#include <iostream>

void RatingManager::addRating(int userId, int movieId, double score) {
    ratings.push_back(Rating(userId, movieId, score));
    std::cout << "평점이 저장되었습니다." << std::endl;
}

void RatingManager::printAllRatings() const {
    if (ratings.empty()) {
        std::cout << "등록된 평점이 없습니다." << std::endl;
        return;
    }

    for (const Rating& rating : ratings) {
        std::cout << rating << std::endl;
    }
}

void RatingManager::printRatingsByMovie(int movieId) const {
    bool found = false;

    for (const Rating& rating : ratings) {
        if (rating.getMovieId() == movieId) {
            std::cout << rating << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "해당 영화의 평점이 없습니다." << std::endl;
    }
}