#pragma once        // 헤더 파일이 여러 번 포함되는 것을 방지하기 위한 지시문
#include <string>   // std::string을 사용하기 위해 포함
#include <iostream> // std::ostream을 사용하기 위해 포함

class Movie {   // 영화 1개의 정보를 저장하고 관련 기능을 제공하는 클래스
private:
    int id;                  // 영화 고유 번호
    std::string title;       // 영화 제목
    std::string genre;       // 영화 장르
    int releaseYear;         // 영화 개봉 연도
    double totalRating;      // 지금까지 받은 평점 총합
    int ratingCount;         // 지금까지 받은 평점 개수

public:
    Movie();   // 기본 생성자: 매개변수 없이 Movie 객체를 만들 때 사용
    Movie(int id, const std::string& title,
          const std::string& genre, int year);  
    // 매개변수 생성자: 영화 정보를 전달받아 객체를 생성할 때 사용

    int getId() const;                 // 영화 id를 반환하는 getter 함수
    std::string getTitle() const;      // 영화 제목을 반환하는 getter 함수
    std::string getGenre() const;      // 영화 장르를 반환하는 getter 함수
    int getReleaseYear() const;        // 개봉 연도를 반환하는 getter 함수
    double getAverageRating() const;   // 평균 평점을 계산해서 반환하는 함수
    int getRatingCount() const;        // 평점 개수를 반환하는 getter 함수

    bool addRating(double r);   // 평점을 추가하는 함수. 성공하면 true, 실패하면 false 반환
    void display() const;       // 영화 정보를 화면에 출력하는 함수

    bool operator==(const Movie& other) const;   // 두 영화가 같은지 비교하는 연산자
    bool operator<(const Movie& other) const;    // 두 영화를 정렬 기준에 따라 비교하는 연산자

    friend std::ostream& operator<<(std::ostream& os, const Movie& movie);
    // Movie 객체를 cout으로 출력할 수 있게 해주는 friend 전역 함수
    // friend를 쓰면 클래스 외부 함수가 private 멤버에도 접근 가능
};

/*
========================
Movie.h 예상 질문 & 답변
========================

// Q1. 왜 Movie 클래스를 만들었나요?
// A1. 영화 한 개의 정보(id, 제목, 장르, 개봉연도, 평점 정보)를 하나의 객체로 묶어 관리하기 위해 만들었습니다.
//     데이터와 기능을 함께 묶는 캡슐화를 적용한 것입니다.

// Q2. 멤버변수를 private으로 둔 이유는 무엇인가요?
// A2. 외부에서 직접 값을 바꾸지 못하게 해서 데이터를 보호하기 위해서입니다.
//     예를 들어 totalRating이나 ratingCount를 마음대로 수정하면 평균 평점이 틀어질 수 있으므로,
//     허용된 함수(addRating, getter 등)를 통해서만 접근하도록 했습니다.

// Q3. totalRating와 ratingCount를 따로 둔 이유는 무엇인가요?
// A3. 평균 평점을 계산하기 위해서입니다.
//     평점 하나하나를 모두 저장하지 않아도 총합과 개수만 있으면 평균을 구할 수 있기 때문입니다.

// Q4. 왜 getter 함수를 만들었나요?
// A4. private 멤버변수에 직접 접근할 수 없으므로,
//     필요한 값만 안전하게 읽어갈 수 있도록 getter 함수를 제공했습니다.

// Q5. getter 함수에 const를 붙인 이유는 무엇인가요?
// A5. getter는 객체의 상태를 바꾸지 않고 값만 읽어오기 때문입니다.
//     const를 붙이면 const 객체에서도 호출할 수 있고, 읽기 전용 함수라는 의미가 분명해집니다.

// Q6. addRating()는 왜 public인가요?
// A6. 외부에서 영화에 평점을 추가할 수 있어야 하기 때문입니다.
//     하지만 totalRating와 ratingCount를 직접 수정하게 하지 않고,
//     addRating()를 통해서만 유효성 검사 후 수정하도록 만들었습니다.

// Q7. display() 함수가 왜 필요한가요?
// A7. Movie 객체의 정보를 출력하는 역할을 한 곳에 모으기 위해서입니다.
//     출력 방식을 클래스 내부 기능으로 제공하면 재사용이 쉽고 코드가 깔끔해집니다.

// Q8. operator==를 선언한 이유는 무엇인가요?
// A8. Movie 객체끼리 같은 영화인지 비교할 수 있도록 하기 위해서입니다.
//     일반 int나 string처럼 사용자 정의 타입도 == 연산을 사용할 수 있게 만들었습니다.

// Q9. operator<를 선언한 이유는 무엇인가요?
// A9. Movie 객체들을 정렬할 수 있도록 기준을 정의하기 위해서입니다.
//     sort() 같은 STL 알고리즘이 이 연산자를 사용해 객체를 비교합니다.

// Q10. operator<<를 friend로 선언한 이유는 무엇인가요?
// A10. cout << movie 형태로 출력하기 위해 전역 함수로 선언했고,
//      출력 함수 안에서 private 멤버(id, title 등)에 접근할 수 있도록 friend를 사용했습니다.

// Q11. 생성자가 2개인 이유는 무엇인가요?
// A11. 기본 생성자는 빈 객체 생성용이고,
//      매개변수 생성자는 실제 영화 정보를 넣어 바로 객체를 만들기 위해서입니다.
//      상황에 따라 다른 방식으로 객체를 생성할 수 있도록 오버로딩했습니다.
*/