#include "MovieManager.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <set>
#include <utility>

void MovieManager::sortMoviesById() {
    std::sort(movies.begin(), movies.end(),
        [](const Movie& a, const Movie& b) {
            return a.getId() < b.getId();
        }
    );
}

void MovieManager::addMovie(int id, const std::string& title,
                            const std::string& genre, int year) {
    for (const Movie& movie : movies) {
        if (movie.getId() == id) {
            std::cout << "이미 존재하는 영화 ID입니다." << std::endl;
            return;
        }
    }

    movies.push_back(Movie(id, title, genre, year));
    sortMoviesById();

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

            return movie.addRating(score);
        }
    }

    return false;
}

const Movie* MovieManager::findById(int movieId) const {
    for (const Movie& movie : movies) {
        if (movie.getId() == movieId) {
            return &movie;
        }
    }

    return nullptr;
}

double MovieManager::calculateGenreSimilarity(
    const std::string& genre,
    const std::vector<Rating>& userRatings
) const {
    double scoreSum = 0.0;
    int count = 0;

    for (const Rating& rating : userRatings) {
        const Movie* watchedMovie = findById(rating.getMovieId());

        if (watchedMovie == nullptr) {
            continue;
        }

        if (watchedMovie->getGenre() == genre && rating.getScore() >= 4.0) {
            scoreSum += rating.getScore();
            count++;
        }
    }

    if (count == 0) {
        return 0.0;
    }

    return scoreSum / count;
}

std::vector<Movie> MovieManager::recommend(
    const std::vector<Rating>& userRatings,
    int n
) const {
    std::vector<Movie> result;

    if (userRatings.empty() || n <= 0) {
        return result;
    }

    std::set<int> watchedMovieIds;

    for (const Rating& rating : userRatings) {
        watchedMovieIds.insert(rating.getMovieId());
    }

    std::vector<std::pair<Movie, double>> scoredMovies;

    for (const Movie& candidate : movies) {
        if (watchedMovieIds.find(candidate.getId()) != watchedMovieIds.end()) {
            continue;
        }

        double genreSimilarity = calculateGenreSimilarity(
            candidate.getGenre(),
            userRatings
        );

        if (genreSimilarity <= 0.0) {
            continue;
        }

        double finalScore = genreSimilarity * 10.0
                          + candidate.getAverageRating();

        scoredMovies.push_back({candidate, finalScore});
    }

    std::sort(scoredMovies.begin(), scoredMovies.end(),
        [](const std::pair<Movie, double>& a,
           const std::pair<Movie, double>& b) {
            if (a.second == b.second) {
                return a.first.getId() < b.first.getId();
            }

            return a.second > b.second;
        }
    );

    int count = std::min(n, static_cast<int>(scoredMovies.size()));

    for (int i = 0; i < count; i++) {
        result.push_back(scoredMovies[i].first);
    }

    return result;
}

void MovieManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: " << filename << " 파일을 열 수 없습니다." << std::endl;
        return;
    }

    movies.clear();

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);
        std::string token;

        int id;
        std::string title;
        std::string genre;
        int releaseYear;

        std::getline(ss, token, ',');
        id = std::stoi(token);

        std::getline(ss, title, ',');

        std::getline(ss, genre, ',');

        std::getline(ss, token, ',');
        releaseYear = std::stoi(token);

        movies.push_back(Movie(id, title, genre, releaseYear));
    }

    sortMoviesById();

    file.close();

    std::cout << filename << " 로드 완료: " << movies.size() << "건" << std::endl;
}

void MovieManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: " << filename << " 파일 저장 실패" << std::endl;
        return;
    }

    file << "id,title,genre,releaseYear" << std::endl;

    for (const Movie& movie : movies) {
        file << movie.getId() << ","
             << movie.getTitle() << ","
             << movie.getGenre() << ","
             << movie.getReleaseYear() << std::endl;
    }

    file.close();

    std::cout << filename << " 저장 완료: " << movies.size() << "건" << std::endl;
}

int MovieManager::size() const {
    return static_cast<int>(movies.size());
}