#include "MovieRecommenderApp.h"
#include "Constants.h"
#include <iostream>
#include <string>
#include <vector>
#include <limits>

namespace MenuOption {
    constexpr int EXIT = 0;
    constexpr int ADD_MOVIE = 1;
    constexpr int SEARCH_MOVIE = 2;
    constexpr int PRINT_ALL_MOVIES = 3;
    constexpr int PRINT_MOVIES_BY_RATING = 4;
    constexpr int ADD_USER = 5;
    constexpr int PRINT_ALL_USERS = 6;
    constexpr int ADD_RATING = 7;
    constexpr int PRINT_RATINGS_BY_MOVIE = 8;
    constexpr int PRINT_ALL_RATINGS = 9;
    constexpr int COMPARE_USER_SIMILARITY = 10;
    constexpr int RECOMMEND_MOVIES = 11;
    constexpr int FILTER_BY_GENRE = 13;
}

MovieRecommenderApp::MovieRecommenderApp()
    : movieManager(),
      userManager(),
      ratingManager(),
      recommender(movieManager, ratingManager) {}

void MovieRecommenderApp::clearInputLine() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void MovieRecommenderApp::loadData() {
    movieManager.loadFromFile("data/movies.csv");
    userManager.loadFromFile("data/users.csv");
    ratingManager.loadFromFile("data/ratings.csv");
}

void MovieRecommenderApp::saveData() const {
    movieManager.saveToFile("data/movies.csv");
    userManager.saveToFile("data/users.csv");
    ratingManager.saveToFile("data/ratings.csv");
}

void MovieRecommenderApp::rebuildMovieRatings() {
    for (const Rating& rating : ratingManager.getRatings()) {
        if (rating.isValid()) {
            movieManager.addRatingToMovie(
                rating.getMovieId(),
                rating.getScore()
            );
        }
    }
}

void MovieRecommenderApp::printMenu() const {
    std::cout << "\n===== Movie Recommender Menu =====" << std::endl;
    std::cout << "1. 영화 추가" << std::endl;
    std::cout << "2. 제목으로 영화 검색" << std::endl;
    std::cout << "3. 전체 영화 목록 출력" << std::endl;
    std::cout << "4. 평점순 영화 목록 출력" << std::endl;
    std::cout << "5. 사용자 추가" << std::endl;
    std::cout << "6. 전체 사용자 목록 출력" << std::endl;
    std::cout << "7. 평점 입력" << std::endl;
    std::cout << "8. 특정 영화의 평점 목록 출력" << std::endl;
    std::cout << "9. 전체 평점 목록 출력" << std::endl;
    std::cout << "10. 사용자 유사도 비교" << std::endl;
    std::cout << "11. 영화 추천" << std::endl;
    std::cout << "13. 장르별 영화 보기" << std::endl;
    std::cout << "0. 종료" << std::endl;
    std::cout << "메뉴 선택: ";
}

void MovieRecommenderApp::handleAddMovie() {
    int id;
    int year;
    std::string title;
    std::string genre;

    std::cout << "영화 ID: ";
    std::cin >> id;
    clearInputLine();

    std::cout << "영화 제목: ";
    std::getline(std::cin, title);

    std::cout << "장르: ";
    std::getline(std::cin, genre);

    std::cout << "개봉 연도: ";
    std::cin >> year;

    movieManager.addMovie(id, title, genre, year);
}

void MovieRecommenderApp::handleSearchMovie() {
    std::string title;

    clearInputLine();

    std::cout << "검색할 제목: ";
    std::getline(std::cin, title);

    movieManager.searchByTitle(title);
}

void MovieRecommenderApp::handleAddUser() {
    int id;
    std::string name;
    std::string email;

    std::cout << "사용자 ID: ";
    std::cin >> id;
    clearInputLine();

    std::cout << "이름: ";
    std::getline(std::cin, name);

    std::cout << "이메일: ";
    std::getline(std::cin, email);

    userManager.addUser(id, name, email);
}

void MovieRecommenderApp::handleAddRating() {
    int userId;
    int movieId;
    double score;

    std::cout << "사용자 ID: ";
    std::cin >> userId;

    std::cout << "영화 ID: ";
    std::cin >> movieId;

    std::cout << "평점: ";
    std::cin >> score;

    if (!userManager.hasUser(userId)) {
        std::cout << "존재하지 않는 사용자 ID입니다." << std::endl;
        return;
    }

    if (!movieManager.hasMovie(movieId)) {
        std::cout << "존재하지 않는 영화 ID입니다." << std::endl;
        return;
    }

    if (score < AppConstants::MIN_RATING ||
        score > AppConstants::MAX_RATING) {
        std::cout << "평점은 "
                  << AppConstants::MIN_RATING
                  << " 이상 "
                  << AppConstants::MAX_RATING
                  << " 이하만 입력할 수 있습니다."
                  << std::endl;
        return;
    }

    if (ratingManager.hasRating(userId, movieId)) {
        std::cout << "이미 해당 사용자가 이 영화에 평점을 입력했습니다."
                  << std::endl;
        return;
    }

    if (ratingManager.addRating(userId, movieId, score)) {
        movieManager.addRatingToMovie(movieId, score);
        std::cout << "평점이 정상적으로 입력되었습니다." << std::endl;
    } else {
        std::cout << "평점 저장에 실패했습니다." << std::endl;
    }
}

void MovieRecommenderApp::handlePrintRatingsByMovie() {
    int movieId;

    std::cout << "영화 ID 입력: ";
    std::cin >> movieId;

    ratingManager.printRatingsByMovie(movieId);
}

void MovieRecommenderApp::handleSimilarityComparison() {
    int targetUserId;

    std::cout << "기준 사용자 ID 입력: ";
    std::cin >> targetUserId;

    if (!userManager.hasUser(targetUserId)) {
        std::cout << "존재하지 않는 사용자 ID입니다." << std::endl;
        return;
    }

    recommender.printSimilarityReport(targetUserId);
}

void MovieRecommenderApp::handleRecommendation() {
    int targetUserId;

    std::cout << "추천 받을 사용자 ID 입력: ";
    std::cin >> targetUserId;

    if (!userManager.hasUser(targetUserId)) {
        std::cout << "존재하지 않는 사용자 ID입니다." << std::endl;
        return;
    }

    std::vector<Rating> targetRatings =
        ratingManager.findByUser(targetUserId);

    if (targetRatings.empty()) {
        std::cout << "해당 사용자의 평점 데이터가 없어 추천할 수 없습니다."
                  << std::endl;
        return;
    }

    std::cout << "\n=== 사용자 기반 협업 필터링 추천 ===" << std::endl;

    recommender.printRecommendations(
        targetUserId,
        AppConstants::DEFAULT_SIMILAR_USER_COUNT,
        AppConstants::DEFAULT_RECOMMENDATION_COUNT
    );

    std::cout << "\n=== 장르 기반 추천 MovieManager::recommend() ==="
              << std::endl;

    std::vector<Movie> genreRecommendations =
        movieManager.recommend(
            targetRatings,
            AppConstants::DEFAULT_RECOMMENDATION_COUNT
        );

    if (genreRecommendations.empty()) {
        std::cout << "장르 기반으로 추천할 영화가 없습니다." << std::endl;
    } else {
        int rank = 1;

        for (const Movie& movie : genreRecommendations) {
            std::cout << rank << ". " << movie << std::endl;
            rank++;
        }
    }
}

void MovieRecommenderApp::handleGenreFilter() {
    std::string genre;

    movieManager.printAvailableGenres();

    clearInputLine();

    std::cout << "\n검색할 장르: ";
    std::getline(std::cin, genre);

    movieManager.printMoviesByGenre(genre);
}

void MovieRecommenderApp::runMenuLoop() {
    int choice;

    do {
        printMenu();
        std::cin >> choice;

        if (choice == MenuOption::ADD_MOVIE) {
            handleAddMovie();
        }

        else if (choice == MenuOption::SEARCH_MOVIE) {
            handleSearchMovie();
        }

        else if (choice == MenuOption::PRINT_ALL_MOVIES) {
            movieManager.printAllMovies();
        }

        else if (choice == MenuOption::PRINT_MOVIES_BY_RATING) {
            movieManager.printMoviesSortedByRating();
        }

        else if (choice == MenuOption::ADD_USER) {
            handleAddUser();
        }

        else if (choice == MenuOption::PRINT_ALL_USERS) {
            userManager.printAllUsers();
        }

        else if (choice == MenuOption::ADD_RATING) {
            handleAddRating();
        }

        else if (choice == MenuOption::PRINT_RATINGS_BY_MOVIE) {
            handlePrintRatingsByMovie();
        }

        else if (choice == MenuOption::PRINT_ALL_RATINGS) {
            ratingManager.printAllRatings();
        }

        else if (choice == MenuOption::COMPARE_USER_SIMILARITY) {
            handleSimilarityComparison();
        }

        else if (choice == MenuOption::RECOMMEND_MOVIES) {
            handleRecommendation();
        }

        else if (choice == MenuOption::FILTER_BY_GENRE) {
            handleGenreFilter();
        }

        else if (choice == MenuOption::EXIT) {
            std::cout << "프로그램을 종료합니다." << std::endl;
        }

        else {
            std::cout << "잘못된 메뉴입니다." << std::endl;
        }

    } while (choice != MenuOption::EXIT);
}

void MovieRecommenderApp::run() {
    loadData();
    rebuildMovieRatings();
    runMenuLoop();
    saveData();
}