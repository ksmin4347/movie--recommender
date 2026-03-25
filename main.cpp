#include "Movie.h"
#include "User.h"
#include "Rating.h"
#include <vector>
#include <iostream>

int main() {
    std::vector<Movie> movies;      //여러 개의 객체를 효율적으로 관리하기 위해 사용
    std::vector<User> users;        //배열 대신 vector를 쓴 이유: 크기가 자동으로 조절되기 때문에 더 유연하게 데이터를 관리
    std::vector<Rating> ratings;

    // 영화 추가
    movies.push_back(Movie(1, "기생충", "드라마", 2019));
    movies.push_back(Movie(2, "인터스텔라", "SF", 2014));
    movies.push_back(Movie(3, "왕과 사는 남자", "사극", 2026));

    // 사용자 추가
    users.push_back(User(1, "김민수", "kim@naver.com"));
    users.push_back(User(2, "성기훈", "giveme456@naver.com"));
    users.push_back(User(3, "김민정", "winter@gmail.com"));
    users.push_back(User(4, "유지민", "karina@naver.com"));

    // 평점 추가
    ratings.push_back(Rating(1, 1, 4.8));
    ratings.push_back(Rating(1, 2, 4.7));
    ratings.push_back(Rating(2, 1, 5.0));
    ratings.push_back(Rating(2, 3, 4.8));
    ratings.push_back(Rating(3, 1, 4.9));
    ratings.push_back(Rating(3, 2, 4.1));
    ratings.push_back(Rating(3, 3, 4.9));
    ratings.push_back(Rating(4, 1, 7.9));
    ratings.push_back(Rating(4, 2, 3.6));
    ratings.push_back(Rating(4, 3, 0.0));


    // Movie에 평점 반영
    movies[0].addRating(4.8);
    movies[1].addRating(4.7);
    movies[0].addRating(5.0);
    movies[2].addRating(4.8);
    movies[0].addRating(4.9);
    movies[1].addRating(4.1);
    movies[2].addRating(4.9);
    movies[0].addRating(7.9);
    movies[1].addRating(3.6);
    movies[2].addRating(0.0);

    std::cout << "=== 영화 목록 ===" << std::endl;
    for (const Movie& m : movies) {
        m.display();
    }

    std::cout << "=== 사용자 목록 ===" << std::endl;
    for (const User& u : users) {
        u.display();
    }

    std::cout << "=== 평점 목록 ===" << std::endl;
    for (const Rating& r : ratings) {
    if (r.getScore() != -1.0) {
        r.display();
    }
    else {
        std::cout << "User: " << r.getUserId()
                  << " Movie: " << r.getMovieId()
                  << " Score: 오류" << std::endl;
    }
}

    return 0;
}