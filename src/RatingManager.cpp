#include "RatingManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

void RatingManager::sortRatingsByUserAndMovie() {
    std::sort(ratings.begin(), ratings.end(),
        [](const Rating& a, const Rating& b) {
            if (a.getUserId() == b.getUserId()) {
                return a.getMovieId() < b.getMovieId();
            }

            return a.getUserId() < b.getUserId();
        }
    );
}

bool RatingManager::addRating(int userId, int movieId, double score) {
    Rating rating(userId, movieId, score);

    if (!rating.isValid()) {    //평점이 유효하지 않으면 false  
        return false;
    }

    if (hasRating(userId, movieId)) {   //이미 같은 유저가 영화를 평가했으면 false
        return false;
    }

    ratings.push_back(rating);
    sortRatingsByUserAndMovie();

    return true;
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

const std::vector<Rating>& RatingManager::getRatings() const {
    return ratings;
}

std::vector<Rating> RatingManager::findByUser(int userId) const {   //특정 사용자가 남긴 평점 목록만 반환
    std::vector<Rating> result;

    for (const Rating& rating : ratings) {
        if (rating.getUserId() == userId && rating.isValid()) {
            result.push_back(rating);
        }
    }

    return result;
}

std::vector<int> RatingManager::getAllUserIds() const { //평점을 남긴 사용자 ID 목록을 중복 없이 반환
    std::vector<int> userIds;       //중복 없는 사용자 id를 저장할 벡터

    for (const Rating& rating : ratings) {//평점 목록 하나씩 확인
        if (!rating.isValid()) {    //유효하지 않으면 건너뛰기
            continue;
        }

        int userId = rating.getUserId();    //현재 평점의 사용자 id 가져옴

        if (std::find(userIds.begin(), userIds.end(), userId) == userIds.end()) {   //find(시작,끝,찾을값)
            userIds.push_back(userId);                                        //찾으면 그 위치 반환, 못찾으면 end()반환
        }                                                                   //못찾으면 그 아이디 저장
    }

    std::sort(userIds.begin(), userIds.end());

    return userIds;
}

bool RatingManager::hasRating(int userId, int movieId) const {
    for (const Rating& rating : ratings) {
        if (rating.getUserId() == userId && rating.getMovieId() == movieId) {
            return true;
        }
    }

    return false;
}

void RatingManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: " << filename << " 파일을 열 수 없습니다." << std::endl;
        return;
    }

    ratings.clear();

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);
        std::string token;

        int userId;
        int movieId;
        double score;

        std::getline(ss, token, ',');
        userId = std::stoi(token);

        std::getline(ss, token, ',');
        movieId = std::stoi(token);

        std::getline(ss, token, ',');
        score = std::stod(token);

        Rating rating(userId, movieId, score);

        if (rating.isValid() && !hasRating(userId, movieId)) {
            ratings.push_back(rating);
        }
    }

    sortRatingsByUserAndMovie();

    file.close();

    std::cout << filename << " 로드 완료: " << ratings.size() << "건" << std::endl;
}

void RatingManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: " << filename << " 파일 저장 실패" << std::endl;
        return;
    }

    file << "userId,movieId,score" << std::endl;

    for (const Rating& rating : ratings) {
        if (rating.isValid()) {
            file << rating.getUserId() << ","
                 << rating.getMovieId() << ","
                 << rating.getScore() << std::endl;
        }
    }

    file.close();

    std::cout << filename << " 저장 완료: " << ratings.size() << "건" << std::endl;
}

int RatingManager::size() const {
    return static_cast<int>(ratings.size());
}