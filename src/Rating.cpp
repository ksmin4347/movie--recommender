#include "Rating.h"      // Rating 클래스 선언을 사용하기 위해 포함
#include <iostream>      // std::cout, std::endl 출력 기능 사용
#include <iomanip>       // std::fixed, std::setprecision 출력 형식 조절

Rating::Rating() : userId(0), movieId(0), score(0.0) {}
// 기본 생성자
// userId, movieId, score를 모두 0으로 초기화
// 객체 생성 시 쓰레기값이 들어가는 것을 방지하기 위함

Rating::Rating(int userId, int movieId, double s)
    : userId(userId), movieId(movieId) {
    // 매개변수 생성자
    // userId와 movieId는 그대로 초기화 리스트로 초기화

    if (s < 0.0 || s > 5.0)
        score = -1.0;   // 잘못된 평점이면 -1.0으로 설정 (에러 상태 표시)
    else
        score = s;      // 정상 범위면 그대로 저장     //main에서 한번 막지만 방어적 프로그래밍으로 한번 더 방지
}

int Rating::getUserId() const { return userId; }
// 사용자 ID 반환
// 객체 상태를 변경하지 않으므로 const

int Rating::getMovieId() const { return movieId; }
// 영화 ID 반환
// 읽기 전용 함수이므로 const

double Rating::getScore() const { return score; }
// 평점 점수 반환
// 객체 상태를 변경하지 않으므로 const

bool Rating::isValid() const {
    return score != -1.0;
}
// 평점이 유효한지 확인하는 함수
// -1.0이면 잘못된 값이므로 false
// 그 외 값이면 정상 평점이므로 true

void Rating::display() const {
    std::cout << *this << std::endl;
}
// Rating 객체를 출력하는 함수
// 실제 출력 형식은 operator<<에 맡기고, display는 출력 요청만 수행

std::ostream& operator<<(std::ostream& os, const Rating& rating) {
    // Rating 객체를 cout으로 출력하기 위한 연산자 오버로딩 함수

    os << "User: " << rating.getUserId()
       << " Movie: " << rating.getMovieId()
       << " Score: ";
    // 사용자 ID, 영화 ID, 평점 출력 형식 구성

    if (rating.isValid()) {
        os << std::fixed << std::setprecision(1) << rating.getScore();
        // 유효한 평점이면 소수점 첫째 자리까지 출력
    } else {
        os << "오류";
        // 잘못된 평점이면 "오류" 출력
    }

    return os;
    // ostream을 반환해야 cout << rating << endl 같은 연쇄 출력 가능
}

/*
========================
Rating.cpp 예상 질문 & 답변
========================

// Q1. 왜 score가 잘못된 경우 -1.0으로 저장했나요?
// A1. 유효하지 않은 평점을 표시하기 위한 "에러 값"으로 사용했습니다.
//     double 타입이기 때문에 음수(-1.0)를 특별한 상태값으로 사용했습니다.

// Q2. isValid() 함수는 왜 만들었나요?
// A2. score가 정상 값인지 확인하기 위해서입니다.
//     출력이나 처리할 때 오류 상태인지 쉽게 판단할 수 있도록 만들었습니다.

// Q3. 생성자에서 왜 유효성 검사를 하나요?
// A3. 잘못된 평점이 객체에 저장되는 것을 막기 위해서입니다.
//     객체가 생성될 때부터 항상 올바른 상태를 유지하도록 하기 위함입니다.

// Q4. getter 함수에 const를 붙인 이유는 무엇인가요?
// A4. 이 함수들은 멤버변수를 변경하지 않고 값을 읽기만 하기 때문입니다.
//     const를 붙이면 const 객체에서도 사용할 수 있고, 안전성을 높일 수 있습니다.

// Q5. display() 함수에서 왜 직접 출력하지 않고 *this를 사용했나요?
// A5. 출력 형식을 operator<<에 모아두기 위해서입니다.
//     이렇게 하면 출력 로직을 한 곳에서 관리할 수 있어서 유지보수가 쉽습니다.

// Q6. operator<<는 왜 전역 함수인가요?
// A6. cout << rating 형태에서 왼쪽 피연산자가 cout이기 때문입니다.
//     따라서 멤버 함수가 아니라 전역 함수로 정의해야 합니다.

// Q7. operator<<에서 getter를 사용하는 이유는 무엇인가요?
// A7. private 멤버에 직접 접근하지 않고,
//     캡슐화를 유지하면서 안전하게 값을 가져오기 위해 getter를 사용했습니다.

// Q8. 왜 fixed와 setprecision을 사용했나요?
// A8. 평점을 항상 소수점 한 자리까지 일정한 형식으로 출력하기 위해 사용했습니다.

// Q9. Rating 클래스의 역할은 무엇인가요?
// A9. "누가(userId) 어떤 영화(movieId)에 몇 점(score)을 줬는지"를 저장하는 역할입니다.
//     즉, 평점 하나를 나타내는 데이터 클래스입니다.

// Q10. Movie 클래스에도 평점이 있는데 왜 Rating 클래스가 따로 있나요?
// A10. Movie는 평균 평점 같은 "요약 정보"를 저장하고,
//      Rating은 개별 평점 기록(누가 몇 점 줬는지)을 저장하기 위해 분리했습니다.
*/