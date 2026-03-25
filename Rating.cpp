#include "Rating.h"
#include <iostream>

Rating::Rating() : userId(0), movieId(0), score(0.0) {}

Rating::Rating(int userId, int movieId, double s)   //매개변수 이름 왜 s?: 멤버변수와 이름 겹치지 않게 함.
    : userId(userId), movieId(movieId) {

    // ⭐ 유효성 검사 (핵심)
    if (s < 0.0 || s > 5.0)     //잘못된 평점 입력 방지하기 위함
        score = -1.0;
    else
        score = s;
}

int Rating::getUserId() const { return userId; }
int Rating::getMovieId() const { return movieId; }
double Rating::getScore() const { return score; }

void Rating::display() const {
    std::cout << "User: " << userId
              << " Movie: " << movieId
              << " Score: " << score << std::endl;
}