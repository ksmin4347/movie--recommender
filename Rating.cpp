#include "Rating.h"
#include <iostream>
#include <iomanip>

Rating::Rating() : userId(0), movieId(0), score(0.0) {}

Rating::Rating(int userId, int movieId, double s)
    : userId(userId), movieId(movieId) {
    if (s < 0.0 || s > 5.0)
        score = -1.0;
    else
        score = s;
}

int Rating::getUserId() const { return userId; }
int Rating::getMovieId() const { return movieId; }
double Rating::getScore() const { return score; }

bool Rating::isValid() const {
    return score != -1.0;
}

void Rating::display() const {
    std::cout << *this << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Rating& rating) {
    os << "User: " << rating.getUserId()
       << " Movie: " << rating.getMovieId()
       << " Score: ";

    if (rating.isValid()) {
        os << std::fixed << std::setprecision(1) << rating.getScore();
    } else {
        os << "오류";
    }
    return os;
}