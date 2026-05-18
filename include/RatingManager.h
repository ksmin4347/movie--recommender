#pragma once

#include "BaseManager.h"
#include "Rating.h"
#include <vector>
#include <string>

class RatingManager : public BaseManager {
private:
    std::vector<Rating> ratings;

public:
    void addRating(int userId, int movieId, double score);

    void printAllRatings() const;

    void printRatingsByMovie(int movieId) const;

    const std::vector<Rating>& getRatings() const;

    void loadFromFile(const std::string& filename) override;
    void saveToFile(const std::string& filename) const override;
    int size() const override;
};