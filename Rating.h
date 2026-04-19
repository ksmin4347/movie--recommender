#pragma once
#include <iostream>

class Rating {
private:
    int userId;
    int movieId;
    double score;

public:
    Rating();
    Rating(int userId, int movieId, double score);

    int getUserId() const;
    int getMovieId() const;
    double getScore() const;
    bool isValid() const;

    void display() const;

    friend std::ostream& operator<<(std::ostream& os, const Rating& rating);
};