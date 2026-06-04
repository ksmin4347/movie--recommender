#include "RatingManager.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <exception>

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

    if (!rating.isValid()) {
        return false;
    }

    if (hasRating(userId, movieId)) {
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

std::vector<Rating> RatingManager::findByUser(int userId) const {
    std::vector<Rating> result;

    for (const Rating& rating : ratings) {
        if (rating.getUserId() == userId && rating.isValid()) {
            result.push_back(rating);
        }
    }

    return result;
}

std::vector<int> RatingManager::getAllUserIds() const {
    std::vector<int> userIds;

    for (const Rating& rating : ratings) {
        if (!rating.isValid()) {
            continue;
        }

        int userId = rating.getUserId();

        if (std::find(userIds.begin(), userIds.end(), userId) == userIds.end()) {
            userIds.push_back(userId);
        }
    }

    std::sort(userIds.begin(), userIds.end());

    return userIds;
}

bool RatingManager::hasRating(int userId, int movieId) const {
    for (const Rating& rating : ratings) {
        if (rating.getUserId() == userId &&
            rating.getMovieId() == movieId) {
            return true;
        }
    }

    return false;
}

void RatingManager::loadFromFile(const std::string& filename) {
    std::ifstream file;

    if (!openInputFile(file, filename)) {
        return;
    }

    ratings.clear();
    skipHeader(file);

    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        std::vector<std::string> fields = splitCsvLine(line);

        if (fields.size() != 3) {
            std::cerr << "CSV 형식 오류: " << line << std::endl;
            continue;
        }

        try {
            int userId = std::stoi(fields[0]);
            int movieId = std::stoi(fields[1]);
            double score = std::stod(fields[2]);

            Rating rating(userId, movieId, score);

            if (rating.isValid() && !hasRating(userId, movieId)) {
                ratings.push_back(rating);
            }
        } catch (const std::exception& e) {
            std::cerr << "CSV 파싱 오류: " << line
                      << " (" << e.what() << ")"
                      << std::endl;
        }
    }

    sortRatingsByUserAndMovie();
    file.close();

    printLoadComplete(filename, size());
}

void RatingManager::saveToFile(const std::string& filename) const {
    std::ofstream file;

    if (!openOutputFile(file, filename)) {
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

    printSaveComplete(filename, size());
}

int RatingManager::size() const {
    return static_cast<int>(ratings.size());
}