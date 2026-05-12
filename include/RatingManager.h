#pragma once               // 헤더 파일 중복 포함 방지
#include "Rating.h"        // Rating 클래스를 사용하기 위해 포함
#include <vector>          // 여러 Rating 객체를 저장하기 위해 vector 사용

class RatingManager {   // 여러 개의 Rating 객체를 관리하는 클래스
private:
    std::vector<Rating> ratings;
    // 평점들을 저장하는 컨테이너
    // 동적으로 크기가 증가

public:
    void addRating(int userId, int movieId, double score);
    // 새로운 평점을 추가하는 함수

    void printAllRatings() const;
    // 전체 평점 목록 출력 함수

    void printRatingsByMovie(int movieId) const;
    // 특정 영화의 평점 목록 출력 함수
};

/*
========================
RatingManager.h 예상 질문 & 답변
========================

// Q1. RatingManager의 역할은 무엇인가요?
// A1. 여러 개의 Rating 객체를 저장하고,
//     평점 데이터를 관리하는 역할을 합니다.

// Q2. 왜 vector를 사용했나요?
// A2. 평점 개수가 동적으로 변하기 때문에,
//     크기가 자동으로 늘어나는 vector를 사용했습니다.

// Q3. ratings를 private으로 둔 이유는 무엇인가요?
// A3. 외부에서 직접 접근해서 데이터를 수정하지 못하도록 하기 위해서입니다.
//     캡슐화를 적용한 것입니다.

// Q4. 함수에 const를 붙인 이유는 무엇인가요?
// A4. 해당 함수들이 객체 상태를 변경하지 않기 때문입니다.
//     안전성과 가독성을 위해 const를 붙였습니다.

// Q5. addRating은 왜 const가 아닌가요?
// A5. 새로운 데이터를 추가해서 vector를 변경하기 때문입니다.

// Q6. printRatingsByMovie는 왜 필요한가요?
// A6. 특정 영화에 대한 평점만 따로 조회할 수 있도록 하기 위해서입니다.

// Q7. RatingManager와 MovieManager는 어떻게 연결되나요?
// A7. main에서 같이 사용됩니다.
//     RatingManager는 평점 기록을 저장하고,
//     MovieManager는 평균 평점 계산을 담당합니다.
*/