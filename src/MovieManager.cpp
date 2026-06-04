#include "MovieManager.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <set>
#include <utility>
#include <cmath>
#include <exception>

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
    return findById(movieId) != nullptr;
}

bool MovieManager::addRatingToMovie(int movieId, double score) {
    for (Movie& movie : movies) {
        if (movie.getId() == movieId) {
            if (score < AppConstants::MIN_RATING ||
                score > AppConstants::MAX_RATING) {
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

        if (watchedMovie->getGenre() == genre &&
            rating.getScore() >= AppConstants::HIGH_RATING_THRESHOLD) {
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

        if (genreSimilarity <= AppConstants::MIN_RATING) {
            continue;
        }

        double finalScore = genreSimilarity *
                            AppConstants::GENRE_SIMILARITY_WEIGHT
                            + candidate.getAverageRating();

        scoredMovies.push_back({candidate, finalScore});
    }

    std::sort(scoredMovies.begin(), scoredMovies.end(),
        [](const std::pair<Movie, double>& a,
           const std::pair<Movie, double>& b) {
            if (std::abs(a.second - b.second) < AppConstants::EPSILON) {
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
    std::ifstream file;

    if (!openInputFile(file, filename)) {
        return;
    }

    movies.clear();
    skipHeader(file);

    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        std::vector<std::string> fields = splitCsvLine(line);

        if (fields.size() != 4) {
            std::cerr << "CSV 형식 오류: " << line << std::endl;
            continue;
        }

        try {
            int id = std::stoi(fields[0]);
            std::string title = fields[1];
            std::string genre = fields[2];
            int releaseYear = std::stoi(fields[3]);

            movies.push_back(Movie(id, title, genre, releaseYear));
        } catch (const std::exception& e) {
            std::cerr << "CSV 파싱 오류: " << line
                      << " (" << e.what() << ")"
                      << std::endl;
        }
    }

    sortMoviesById();
    file.close();

    printLoadComplete(filename, size());
}

void MovieManager::saveToFile(const std::string& filename) const {
    std::ofstream file;

    if (!openOutputFile(file, filename)) {
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

    printSaveComplete(filename, size());
}

int MovieManager::size() const {
    return static_cast<int>(movies.size());
}