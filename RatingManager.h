#pragma once
#include "Rating.h"
#include <vector>

class RatingManager {
private:
    std::vector<Rating> ratings;

public:
    void addRating(int userId, int movieId, double score);
    void printAllRatings() const;
    void printRatingsByMovie(int movieId) const;
};