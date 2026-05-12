#pragma once          // 헤더 중복 포함 방지
#include <iostream>   // ostream 사용을 위해 포함

class Rating {   // 하나의 평점 데이터를 나타내는 클래스
private:
    int userId;     // 평점을 남긴 사용자 ID
    int movieId;    // 평점을 받은 영화 ID
    double score;   // 평점 점수

public:
    Rating();   // 기본 생성자

    Rating(int userId, int movieId, double score);
    // 매개변수 생성자: 사용자, 영화, 점수를 받아 객체 생성

    int getUserId() const;    // 사용자 ID 반환
    int getMovieId() const;   // 영화 ID 반환
    double getScore() const;  // 평점 반환

    bool isValid() const;     // 평점이 유효한지 확인하는 함수

    void display() const;     // 평점 정보 출력 함수

    friend std::ostream& operator<<(std::ostream& os, const Rating& rating);
    // Rating 객체를 cout으로 출력하기 위한 연산자 오버로딩
};

/*
========================
Rating.h 예상 질문 & 답변
========================

// Q1. Rating 클래스는 왜 필요한가요?
// A1. 한 개의 평점 정보를 저장하기 위해서입니다.
//     사용자 ID, 영화 ID, 점수를 묶어서 하나의 객체로 관리합니다.

// Q2. userId와 movieId를 같이 저장하는 이유는 무엇인가요?
// A2. 어떤 사용자가 어떤 영화에 평점을 줬는지 연결 정보를 저장하기 위해서입니다.

// Q3. score를 double로 한 이유는 무엇인가요?
// A3. 평점이 4.5 같은 소수점 값을 가질 수 있기 때문에 double 타입을 사용했습니다.

// Q4. isValid() 함수는 왜 public인가요?
// A4. 외부에서 이 평점이 유효한지 확인해야 하기 때문입니다.
//     출력이나 로직 처리에서 필요합니다.

// Q5. display() 함수가 필요한 이유는 무엇인가요?
// A5. Rating 객체의 출력 기능을 클래스 내부에서 제공하기 위해서입니다.
//     객체지향적으로 데이터와 기능을 묶기 위함입니다.

// Q6. operator<<를 friend로 선언한 이유는 무엇인가요?
// A6. private 멤버에 접근해서 출력하기 위해서입니다.
//     friend를 사용하면 클래스 외부 함수에서도 접근이 가능합니다.

// Q7. 이 클래스의 핵심 역할은 무엇인가요?
// A7. "평점 하나"를 표현하는 데이터 클래스입니다.
//     즉, Rating은 가장 작은 단위의 데이터입니다.
*/