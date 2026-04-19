#include "MovieManager.h"
#include <iostream>
#include <algorithm>

void MovieManager::addMovie(int id, const std::string& title,
                            const std::string& genre, int year) {
    for (const Movie& movie : movies) {
        if (movie.getId() == id) {
            std::cout << "이미 존재하는 영화 ID입니다." << std::endl;
            return;
        }
    }

    movies.push_back(Movie(id, title, genre, year));
    std::cout << "영화가 추가되었습니다." << std::endl;
}

void MovieManager::printAllMovies() const {
    if (movies.empty()) {
        std::cout << "등록된 영화가 없습니다." << std::endl;
        return;
    }

    for (const Movie& movie : movies) {
        std::cout << movie << std::endl;
    }
}

void MovieManager::searchByTitle(const std::string& title) const {
    bool found = false;

    for (const Movie& movie : movies) {
        if (movie.getTitle() == title) {
            std::cout << movie << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "해당 제목의 영화가 없습니다." << std::endl;
    }
}

void MovieManager::printMoviesSortedByRating() const {
    if (movies.empty()) {
        std::cout << "등록된 영화가 없습니다." << std::endl;
        return;
    }

    std::vector<Movie> sortedMovies = movies;
    std::sort(sortedMovies.begin(), sortedMovies.end());

    for (const Movie& movie : sortedMovies) {
        std::cout << movie << std::endl;
    }
}

bool MovieManager::hasMovie(int movieId) const {
    for (const Movie& movie : movies) {
        if (movie.getId() == movieId) {
            return true;
        }
    }
    return false;
}

bool MovieManager::addRatingToMovie(int movieId, double score) {
    for (Movie& movie : movies) {
        if (movie.getId() == movieId) {
            if (score < 0.0 || score > 5.0) {
                return false;
            }
            movie.addRating(score);
            return true;
        }
    }
    return false;
}