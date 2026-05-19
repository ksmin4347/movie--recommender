#include "MovieManager.h"
#include "UserManager.h"
#include "RatingManager.h"
#include "Recommender.h"
#include <iostream>
#include <string>
#include <vector>

void printMenu() {
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
    std::cout << "0. 종료" << std::endl;
    std::cout << "메뉴 선택: ";
}

int main() {
    MovieManager movieManager;
    UserManager userManager;
    RatingManager ratingManager;

    movieManager.loadFromFile("data/movies.csv");
    userManager.loadFromFile("data/users.csv");
    ratingManager.loadFromFile("data/ratings.csv");

    for (const Rating& rating : ratingManager.getRatings()) {
        if (rating.isValid()) {
            movieManager.addRatingToMovie(rating.getMovieId(), rating.getScore());
        }
    }

    Recommender recommender(movieManager, ratingManager);

    int choice;

    do {
        printMenu();
        std::cin >> choice;

        if (choice == 1) {
            int id;
            int year;
            std::string title;
            std::string genre;

            std::cout << "영화 ID: ";
            std::cin >> id;
            std::cin.ignore();

            std::cout << "영화 제목: ";
            std::getline(std::cin, title);

            std::cout << "장르: ";
            std::getline(std::cin, genre);

            std::cout << "개봉 연도: ";
            std::cin >> year;

            movieManager.addMovie(id, title, genre, year);
        }

        else if (choice == 2) {
            std::string title;

            std::cin.ignore();

            std::cout << "검색할 제목: ";
            std::getline(std::cin, title);

            movieManager.searchByTitle(title);
        }

        else if (choice == 3) {
            movieManager.printAllMovies();
        }

        else if (choice == 4) {
            movieManager.printMoviesSortedByRating();
        }

        else if (choice == 5) {
            int id;
            std::string name;
            std::string email;

            std::cout << "사용자 ID: ";
            std::cin >> id;
            std::cin.ignore();

            std::cout << "이름: ";
            std::getline(std::cin, name);

            std::cout << "이메일: ";
            std::getline(std::cin, email);

            userManager.addUser(id, name, email);
        }

        else if (choice == 6) {
            userManager.printAllUsers();
        }

        else if (choice == 7) {
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
                continue;
            }

            if (!movieManager.hasMovie(movieId)) {
                std::cout << "존재하지 않는 영화 ID입니다." << std::endl;
                continue;
            }

            if (score < 0.0 || score > 5.0) {
                std::cout << "평점은 0.0 이상 5.0 이하만 입력할 수 있습니다." << std::endl;
                continue;
            }

            if (ratingManager.hasRating(userId, movieId)) {
                std::cout << "이미 해당 사용자가 이 영화에 평점을 입력했습니다." << std::endl;
                continue;
            }

            if (ratingManager.addRating(userId, movieId, score)) {
                movieManager.addRatingToMovie(movieId, score);
                std::cout << "평점이 정상적으로 입력되었습니다." << std::endl;
            } else {
                std::cout << "평점 저장에 실패했습니다." << std::endl;
            }
        }

        else if (choice == 8) {
            int movieId;

            std::cout << "영화 ID 입력: ";
            std::cin >> movieId;

            ratingManager.printRatingsByMovie(movieId);
        }

        else if (choice == 9) {
            ratingManager.printAllRatings();
        }

        else if (choice == 10) {
            int targetUserId;

            std::cout << "기준 사용자 ID 입력: ";
            std::cin >> targetUserId;

            if (!userManager.hasUser(targetUserId)) {
                std::cout << "존재하지 않는 사용자 ID입니다." << std::endl;
                continue;
            }

            recommender.printSimilarityReport(targetUserId);
        }

        else if (choice == 11) {
            int targetUserId;

            std::cout << "추천 받을 사용자 ID 입력: ";
            std::cin >> targetUserId;

            if (!userManager.hasUser(targetUserId)) {
                std::cout << "존재하지 않는 사용자 ID입니다." << std::endl;
                continue;
            }

            std::vector<Rating> targetRatings =
                ratingManager.findByUser(targetUserId);

            if (targetRatings.empty()) {
                std::cout << "해당 사용자의 평점 데이터가 없어 추천할 수 없습니다."
                          << std::endl;
                continue;
            }

            std::cout << "\n=== 사용자 기반 추천 ===" << std::endl;
            recommender.printRecommendations(targetUserId, 3, 5);

            std::cout << "\n=== 장르 기반 추천 ===" << std::endl;

            std::vector<Movie> genreRecommendations =
                movieManager.recommend(targetRatings, 5);

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

        else if (choice == 0) {
            std::cout << "프로그램을 종료합니다." << std::endl;
        }

        else {
            std::cout << "잘못된 메뉴입니다." << std::endl;
        }

    } while (choice != 0);

    movieManager.saveToFile("data/movies.csv");
    userManager.saveToFile("data/users.csv");
    ratingManager.saveToFile("data/ratings.csv");

    return 0;
}