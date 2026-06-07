#include "MovieManager.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <set>
#include <utility>
#include <cmath>
#include <exception>
#include <iomanip>

void MovieManager::sortMoviesById() {
    std::sort(movies.begin(), movies.end(),
        [](const Movie& a, const Movie& b) {
            return a.getId() < b.getId();
        }
    );
}

std::string MovieManager::normalizeText(const std::string& text) const {
    std::string result;

    for (char ch : text) {
        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') {
            continue;
        }

        if (ch >= 'A' && ch <= 'Z') {
            result.push_back(ch - 'A' + 'a');
        } else {
            result.push_back(ch);
        }
    }

    return result;
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
    std::string keyword = normalizeText(title);

    if (keyword.empty()) {
        std::cout << "검색어를 입력해주세요." << std::endl;
        return;
    }

    bool found = false;

    for (const Movie& movie : movies) {
        std::string movieTitle = normalizeText(movie.getTitle());

        if (movieTitle.find(keyword) != std::string::npos) {
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

std::vector<Movie> MovieManager::filterByGenre(
    const std::string& genre
) const {
    std::vector<Movie> result;

    std::string keyword = normalizeText(genre);

    if (keyword.empty()) {
        return result;
    }

    for (const Movie& movie : movies) {
        std::string movieGenre = normalizeText(movie.getGenre());

        if (movieGenre.find(keyword) != std::string::npos ||
            keyword.find(movieGenre) != std::string::npos) {
            result.push_back(movie);
        }
    }

    return result;
}

void MovieManager::printMoviesByGenre(const std::string& genre) const {
    std::vector<Movie> filteredMovies = filterByGenre(genre);

    if (normalizeText(genre).empty()) {
        std::cout << "장르를 입력해주세요." << std::endl;
        return;
    }

    if (filteredMovies.empty()) {
        std::cout << "해당 장르의 영화가 없습니다." << std::endl;
        return;
    }

    std::cout << "\n=== " << genre << " 장르 영화 목록 ===" << std::endl;

    for (const Movie& movie : filteredMovies) {
        std::cout << movie << std::endl;
    }
}

std::vector<std::string> MovieManager::getAllGenres() const {
    std::vector<std::string> genres;

    for (const Movie& movie : movies) {
        std::string genre = movie.getGenre();

        if (genre.empty()) {
            continue;
        }

        if (std::find(genres.begin(), genres.end(), genre) == genres.end()) {
            genres.push_back(genre);
        }
    }

    std::sort(genres.begin(), genres.end());

    return genres;
}

void MovieManager::printAvailableGenres() const {
    std::vector<std::string> genres = getAllGenres();

    if (genres.empty()) {
        std::cout << "등록된 장르가 없습니다." << std::endl;
        return;
    }

    std::cout << "\n=== 선택 가능한 장르 목록 ===" << std::endl;

    for (int i = 0; i < static_cast<int>(genres.size()); i++) {
        std::cout << i + 1 << ". " << genres[i] << std::endl;
    }
}

double MovieManager::getOverallAverageRating() const {
    double ratingSum = 0.0;
    int ratedMovieCount = 0;

    for (const Movie& movie : movies) {
        if (movie.getRatingCount() == 0) {
            continue;
        }

        ratingSum += movie.getAverageRating();
        ratedMovieCount++;
    }

    if (ratedMovieCount == 0) {
        return AppConstants::MIN_RATING;
    }

    return ratingSum / ratedMovieCount;
}

std::map<std::string, double> MovieManager::getAverageRatingByGenre() const {
    std::map<std::string, double> ratingSumByGenre;
    std::map<std::string, int> countByGenre;
    std::map<std::string, double> averageByGenre;

    for (const Movie& movie : movies) {
        if (movie.getRatingCount() == 0) {
            continue;
        }

        std::string genre = movie.getGenre();

        ratingSumByGenre[genre] += movie.getAverageRating();
        countByGenre[genre]++;
    }

    for (const auto& item : ratingSumByGenre) {
        const std::string& genre = item.first;
        double ratingSum = item.second;

        if (countByGenre[genre] > 0) {
            averageByGenre[genre] = ratingSum / countByGenre[genre];
        }
    }

    return averageByGenre;
}

std::vector<Movie> MovieManager::getTopNMovies(int n) const {
    std::vector<Movie> ratedMovies;

    if (n <= 0) {
        return ratedMovies;
    }

    for (const Movie& movie : movies) {
        if (movie.getRatingCount() > 0) {
            ratedMovies.push_back(movie);
        }
    }

    std::sort(ratedMovies.begin(), ratedMovies.end(),
        [](const Movie& a, const Movie& b) {
            if (std::abs(a.getAverageRating() - b.getAverageRating())
                < AppConstants::EPSILON) {
                return a.getId() < b.getId();
            }

            return a.getAverageRating() > b.getAverageRating();
        }
    );

    if (static_cast<int>(ratedMovies.size()) > n) {
        ratedMovies.resize(n);
    }

    return ratedMovies;
}

void MovieManager::printOverallAverageRating() const {
    double averageRating = getOverallAverageRating();

    std::cout << std::fixed
              << std::setprecision(AppConstants::OUTPUT_PRECISION);

    if (averageRating == AppConstants::MIN_RATING) {
        std::cout << "평점이 등록된 영화가 없습니다." << std::endl;
        return;
    }

    std::cout << "\n전체 영화 평균 평점: "
              << averageRating
              << std::endl;
}

void MovieManager::printAverageRatingByGenre() const {
    std::map<std::string, double> averageByGenre =
        getAverageRatingByGenre();

    if (averageByGenre.empty()) {
        std::cout << "장르별 평균 평점을 계산할 데이터가 없습니다."
                  << std::endl;
        return;
    }

    std::cout << std::fixed
              << std::setprecision(AppConstants::OUTPUT_PRECISION);

    std::cout << "\n=== 장르별 평균 평점 ===" << std::endl;

    for (const auto& item : averageByGenre) {
        std::cout << item.first << ": "
                  << item.second
                  << std::endl;
    }
}

void MovieManager::printTopNMovies(int n) const {
    std::vector<Movie> topMovies = getTopNMovies(n);

    if (topMovies.empty()) {
        std::cout << "평점이 등록된 영화가 없습니다." << std::endl;
        return;
    }

    std::cout << "\n=== 평점 TOP " << n << " 영화 ===" << std::endl;

    int rank = 1;

    for (const Movie& movie : topMovies) {
        std::cout << rank << ". " << movie << std::endl;
        rank++;
    }
}

double MovieManager::getUserAverageRating(
    const std::vector<Rating>& userRatings
) const {
    if (userRatings.empty()) {
        return AppConstants::MIN_RATING;
    }

    double ratingSum = 0.0;
    int ratingCount = 0;

    for (const Rating& rating : userRatings) {
        if (!rating.isValid()) {
            continue;
        }

        ratingSum += rating.getScore();
        ratingCount++;
    }

    if (ratingCount == 0) {
        return AppConstants::MIN_RATING;
    }

    return ratingSum / ratingCount;
}

std::map<std::string, double> MovieManager::getUserAverageRatingByGenre(
    const std::vector<Rating>& userRatings
) const {
    std::map<std::string, double> ratingSumByGenre;
    std::map<std::string, int> countByGenre;
    std::map<std::string, double> averageByGenre;

    for (const Rating& rating : userRatings) {
        if (!rating.isValid()) {
            continue;
        }

        const Movie* movie = findById(rating.getMovieId());

        if (movie == nullptr) {
            continue;
        }

        std::string genre = movie->getGenre();

        ratingSumByGenre[genre] += rating.getScore();
        countByGenre[genre]++;
    }

    for (const auto& item : ratingSumByGenre) {
        const std::string& genre = item.first;
        double ratingSum = item.second;

        if (countByGenre[genre] > 0) {
            averageByGenre[genre] = ratingSum / countByGenre[genre];
        }
    }

    return averageByGenre;
}

std::vector<std::pair<std::string, double>> MovieManager::getUserTopGenres(
    const std::vector<Rating>& userRatings,
    int n
) const {
    std::vector<std::pair<std::string, double>> topGenres;

    if (n <= 0) {
        return topGenres;
    }

    std::map<std::string, double> averageByGenre =
        getUserAverageRatingByGenre(userRatings);

    for (const auto& item : averageByGenre) {
        topGenres.push_back({item.first, item.second});
    }

    std::sort(topGenres.begin(), topGenres.end(),
        [](const std::pair<std::string, double>& a,
           const std::pair<std::string, double>& b) {
            if (std::abs(a.second - b.second) < AppConstants::EPSILON) {
                return a.first < b.first;
            }

            return a.second > b.second;
        }
    );

    if (static_cast<int>(topGenres.size()) > n) {
        topGenres.resize(n);
    }

    return topGenres;
}

std::vector<std::pair<Movie, double>> MovieManager::getUserTopRatedMovies(
    const std::vector<Rating>& userRatings,
    int n
) const {
    std::vector<std::pair<Movie, double>> topMovies;

    if (n <= 0) {
        return topMovies;
    }

    for (const Rating& rating : userRatings) {
        if (!rating.isValid()) {
            continue;
        }

        const Movie* movie = findById(rating.getMovieId());

        if (movie == nullptr) {
            continue;
        }

        topMovies.push_back({*movie, rating.getScore()});
    }

    std::sort(topMovies.begin(), topMovies.end(),
        [](const std::pair<Movie, double>& a,
           const std::pair<Movie, double>& b) {
            if (std::abs(a.second - b.second) < AppConstants::EPSILON) {
                return a.first.getId() < b.first.getId();
            }

            return a.second > b.second;
        }
    );

    if (static_cast<int>(topMovies.size()) > n) {
        topMovies.resize(n);
    }

    return topMovies;
}

void MovieManager::printUserPreferenceProfile(
    int userId,
    const std::vector<Rating>& userRatings
) const {
    if (userRatings.empty()) {
        std::cout << "해당 사용자의 평점 데이터가 없습니다." << std::endl;
        return;
    }

    double averageRating = getUserAverageRating(userRatings);

    std::vector<std::pair<std::string, double>> topGenres =
        getUserTopGenres(
            userRatings,
            AppConstants::DEFAULT_PROFILE_GENRE_COUNT
        );

    std::vector<std::pair<Movie, double>> topMovies =
        getUserTopRatedMovies(
            userRatings,
            AppConstants::DEFAULT_PROFILE_MOVIE_COUNT
        );

    std::cout << std::fixed
              << std::setprecision(AppConstants::OUTPUT_PRECISION);

    std::cout << "\n=== 사용자 취향 프로필 ===" << std::endl;
    std::cout << "사용자 ID: " << userId << std::endl;
    std::cout << "평가한 영화 수: "
              << userRatings.size()
              << "개" << std::endl;
    std::cout << "사용자 평균 평점: "
              << averageRating
              << std::endl;

    std::cout << "\n선호 장르 TOP "
              << AppConstants::DEFAULT_PROFILE_GENRE_COUNT
              << std::endl;

    if (topGenres.empty()) {
        std::cout << "장르 선호도를 계산할 수 없습니다." << std::endl;
    } else {
        int rank = 1;

        for (const auto& genreInfo : topGenres) {
            std::cout << rank << ". "
                      << genreInfo.first
                      << " - 평균 "
                      << genreInfo.second
                      << std::endl;
            rank++;
        }
    }

    std::cout << "\n높게 평가한 영화 TOP "
              << AppConstants::DEFAULT_PROFILE_MOVIE_COUNT
              << std::endl;

    if (topMovies.empty()) {
        std::cout << "높게 평가한 영화를 찾을 수 없습니다." << std::endl;
    } else {
        int rank = 1;

        for (const auto& movieInfo : topMovies) {
            std::cout << rank << ". "
                      << movieInfo.first
                      << " / 내 평점: "
                      << movieInfo.second
                      << std::endl;
            rank++;
        }
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