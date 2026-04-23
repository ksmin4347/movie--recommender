#include "MovieManager.h"   // MovieManager 클래스 선언을 사용하기 위해 포함
#include <iostream>         // std::cout, std::endl 출력 기능 사용
#include <algorithm>        // std::sort 같은 STL 알고리즘 사용

void MovieManager::addMovie(int id, const std::string& title,
                            const std::string& genre, int year) {
    // 새로운 영화를 추가하는 함수

    for (const Movie& movie : movies) {   // 현재 저장된 모든 영화들을 하나씩 확인
        if (movie.getId() == id) {        // 기존 영화 중 같은 id가 있는지 검사
            std::cout << "이미 존재하는 영화 ID입니다." << std::endl;  // 중복 ID 방지 메시지 출력
            return;   // 중복이면 추가하지 않고 함수 종료
        }
    }

    movies.push_back(Movie(id, title, genre, year));  
    // 중복이 아니면 새로운 Movie 객체를 생성해서 vector에 추가

    std::cout << "영화가 추가되었습니다." << std::endl;   // 추가 완료 메시지 출력
}

void MovieManager::printAllMovies() const {
    // 모든 영화 목록을 출력하는 함수

    if (movies.empty()) {   // vector가 비어있는지 확인
        std::cout << "등록된 영화가 없습니다." << std::endl;   // 아무 영화도 없을 때 메시지 출력
        return;   // 더 진행하지 않고 종료
    }

    for (const Movie& movie : movies) {   // 저장된 모든 영화 순회
        std::cout << movie << std::endl;  // operator<<를 사용하여 영화 출력
    }
}

void MovieManager::searchByTitle(const std::string& title) const {
    // 제목으로 영화를 검색하는 함수

    bool found = false;   // 검색 결과가 있는지 여부를 저장하는 변수

    for (const Movie& movie : movies) {   // 모든 영화 순회
        if (movie.getTitle() == title) {  // 제목이 같은 영화 찾기
            std::cout << movie << std::endl;  // 찾은 영화 출력
            found = true;   // 하나라도 찾았으면 true로 변경
        }
    }

    if (!found) {   // 끝까지 찾지 못한 경우
        std::cout << "해당 제목의 영화가 없습니다." << std::endl;   // 검색 실패 메시지 출력
    }
}

void MovieManager::printMoviesSortedByRating() const {
    // 평점 기준으로 정렬된 영화 목록을 출력하는 함수

    if (movies.empty()) {   // 영화가 하나도 없는 경우
        std::cout << "등록된 영화가 없습니다." << std::endl;
        return;
    }

    std::vector<Movie> sortedMovies = movies;  
    // 원본 movies를 그대로 유지하기 위해 복사본을 생성
    // (정렬하면 순서가 바뀌기 때문)

    std::sort(sortedMovies.begin(), sortedMovies.end());  
    // 정렬 수행
    // Movie 클래스의 operator<가 자동으로 호출됨

    for (const Movie& movie : sortedMovies) {   // 정렬된 결과 출력
        std::cout << movie << std::endl;
    }
}

bool MovieManager::hasMovie(int movieId) const {
    // 특정 ID의 영화가 존재하는지 확인하는 함수

    for (const Movie& movie : movies) {   // 모든 영화 순회
        if (movie.getId() == movieId) {   // id가 일치하면
            return true;   // 존재하므로 true 반환
        }
    }
    return false;   // 끝까지 못 찾으면 false 반환
}

bool MovieManager::addRatingToMovie(int movieId, double score) {
    // 특정 영화에 평점을 추가하는 함수

    for (Movie& movie : movies) {   // 수정해야 하므로 const가 아닌 참조 사용
        if (movie.getId() == movieId) {   // 해당 영화 찾기
            if (score < 0.0 || score > 5.0) {   // 평점 범위 검사
                return false;   // 잘못된 점수면 실패
            }
            movie.addRating(score);   // Movie 객체 내부 함수 호출해서 평점 반영
            return true;   // 성공
        }
    }
    return false;   // 해당 영화가 없으면 실패
}

/*
========================
MovieManager.cpp 예상 질문 & 답변
========================

// Q1. MovieManager 클래스는 왜 필요한가요?
// A1. Movie 객체 하나만으로는 여러 개의 영화를 관리할 수 없기 때문에,
//     vector<Movie>를 이용해 여러 영화 데이터를 저장하고 관리하는 역할을 하기 위해 만들었습니다.

// Q2. movies를 private으로 둔 이유는 무엇인가요?
// A2. 외부에서 movies에 직접 접근하면 데이터가 임의로 수정될 수 있기 때문에,
//     addMovie, searchByTitle 같은 함수들을 통해서만 접근하도록 캡슐화를 적용했습니다.

// Q3. addMovie에서 중복 ID를 검사하는 이유는 무엇인가요?
// A3. 영화 ID는 각 영화를 구별하는 고유한 값이기 때문에,
//     중복되면 어떤 영화인지 구분이 불가능해져서 데이터 무결성이 깨집니다.

// Q4. push_back을 사용하는 이유는 무엇인가요?
// A4. vector에 새로운 Movie 객체를 추가하기 위해서입니다.
//     동적으로 크기가 증가하는 자료구조이기 때문에 편리하게 사용할 수 있습니다.

// Q5. printMoviesSortedByRating에서 왜 복사본을 만들었나요?
// A5. 원본 movies를 정렬하면 기존 순서가 바뀌기 때문에,
//     출력만을 위한 정렬은 복사본에서 수행하도록 했습니다.

// Q6. sort()는 어떻게 동작하나요?
// A6. 내부적으로 Movie 클래스의 operator<를 호출해서 두 객체를 비교하며 정렬합니다.

// Q7. hasMovie 함수는 왜 필요한가요?
// A7. 특정 영화가 존재하는지 확인하기 위해 사용됩니다.
//     특히 평점 입력 전에 존재 여부를 확인해서 잘못된 입력을 방지하는 데 사용됩니다.

// Q8. addRatingToMovie에서 Movie&를 사용한 이유는 무엇인가요?
// A8. 실제 Movie 객체를 수정해야 하기 때문에 참조를 사용했습니다.
//     const를 쓰면 값을 변경할 수 없기 때문입니다.

// Q9. addRatingToMovie에서 score를 다시 검사하는 이유는 무엇인가요?
// A9. main에서도 검사하지만,
//     함수 자체만 따로 호출되더라도 안전하게 동작하도록 방어적 프로그래밍을 적용한 것입니다.

// Q10. searchByTitle에서 found 변수를 둔 이유는 무엇인가요?
// A10. 검색 결과가 하나도 없는 경우를 판단해서
//      "해당 제목의 영화가 없습니다" 메시지를 출력하기 위해 사용했습니다.

// Q11. 이 클래스의 역할을 한 줄로 설명하면?
// A11. 여러 Movie 객체를 저장하고, 추가/검색/정렬/출력 기능을 제공하는 관리 클래스입니다.
*/