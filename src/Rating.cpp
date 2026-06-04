#include "Rating.h"
#include "Constants.h"
#include <iostream>
#include <iomanip>

Rating::Rating()
    : userId(0),
      movieId(0),
      score(AppConstants::MIN_RATING) {}

Rating::Rating(int userId, int movieId, double s)
    : userId(userId), movieId(movieId) {
    if (s < AppConstants::MIN_RATING || s > AppConstants::MAX_RATING) {
        score = AppConstants::INVALID_RATING;
    } else {
        score = s;
    }
}

int Rating::getUserId() const {
    return userId;
}

int Rating::getMovieId() const {
    return movieId;
}

double Rating::getScore() const {
    return score;
}

bool Rating::isValid() const {
    return score != AppConstants::INVALID_RATING;
}

void Rating::display() const {
    std::cout << *this << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Rating& rating) {
    os << "User: " << rating.getUserId()
       << " Movie: " << rating.getMovieId()
       << " Score: ";

    if (rating.isValid()) {
        os << std::fixed
           << std::setprecision(AppConstants::OUTPUT_PRECISION)
           << rating.getScore();
    } else {
        os << "오류";
    }

    return os;
}