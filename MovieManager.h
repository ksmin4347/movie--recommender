#pragma once                // 헤더 파일 중복 포함 방지
#include "Movie.h"          // Movie 클래스를 사용하기 위해 포함
#include <vector>           // 여러 Movie 객체를 저장하기 위한 vector 사용
#include <string>           // 문자열 처리를 위한 string 사용

class MovieManager {   // 여러 개의 Movie 객체를 관리하는 클래스
private:
    std::vector<Movie> movies;   // 영화들을 저장하는 컨테이너 (동적 배열)

public:
    void addMovie(int id, const std::string& title,
                  const std::string& genre, int year);
    // 새로운 영화 추가 함수

    void printAllMovies() const;  
    // 전체 영화 목록 출력 함수 (객체 상태를 변경하지 않으므로 const)

    void searchByTitle(const std::string& title) const;  
    // 제목으로 영화 검색 함수

    void printMoviesSortedByRating() const;  
    // 평점 기준으로 정렬된 영화 출력 함수

    bool hasMovie(int movieId) const;  
    // 특정 ID의 영화가 존재하는지 확인하는 함수

    bool addRatingToMovie(int movieId, double score);  
    // 특정 영화에 평점을 추가하는 함수
};

/*
========================
MovieManager.h 예상 질문 & 답변
========================

// Q1. 왜 vector<Movie>를 사용했나요?
// A1. 영화 개수가 동적으로 변하기 때문에,
//     크기가 자동으로 늘어나는 vector를 사용했습니다.

// Q2. movies를 private으로 둔 이유는 무엇인가요?
// A2. 외부에서 직접 접근하지 못하게 해서 데이터 무결성을 유지하기 위해서입니다.
//     모든 접근은 public 함수들을 통해 이루어지도록 했습니다.

// Q3. 함수에 const가 붙은 이유는 무엇인가요?
// A3. 해당 함수가 멤버변수(movies)를 변경하지 않는다는 것을 명확히 하기 위해서입니다.
//     const를 붙이면 실수로 데이터를 수정하는 것을 방지할 수 있습니다.

// Q4. addMovie는 왜 const가 아닌가요?
// A4. movies에 새로운 데이터를 추가하는 함수이기 때문에
//     객체 상태를 변경하므로 const를 붙일 수 없습니다.

// Q5. searchByTitle의 매개변수를 const std::string&로 받은 이유는 무엇인가요?
// A5. 문자열 복사를 방지해서 성능을 개선하고,
//     함수 내부에서 값을 변경하지 않겠다는 의미를 명확히 하기 위해서입니다.

// Q6. Manager 클래스의 역할은 무엇인가요?
// A6. 데이터를 저장하는 역할과,
//     그 데이터를 처리하는 기능(추가, 검색, 정렬, 출력)을 함께 담당하는 클래스입니다.
*/