#pragma once           // 헤더 파일 중복 포함 방지
#include "User.h"      // User 클래스 사용
#include <vector>      // 여러 User 객체 저장
#include <string>      // 문자열 처리

class UserManager {   // 사용자 여러 명을 관리하는 클래스
private:
    std::vector<User> users;   // 사용자 데이터를 저장하는 컨테이너

public:
    void addUser(int id, const std::string& name, const std::string& email);
    // 새로운 사용자 추가 함수

    void printAllUsers() const;
    // 전체 사용자 목록 출력 함수

    bool hasUser(int userId) const;
    // 특정 ID의 사용자가 존재하는지 확인하는 함수
};

/*
========================
UserManager.h 예상 질문 & 답변
========================

// Q1. 왜 vector<User>를 사용했나요?
// A1. 사용자 수가 동적으로 변하기 때문에,
//     크기가 자동으로 증가하는 vector를 사용했습니다.

// Q2. users를 private으로 둔 이유는 무엇인가요?
// A2. 외부에서 직접 데이터를 수정하지 못하게 해서,
//     캡슐화를 유지하기 위해서입니다.

// Q3. 함수에 const를 붙인 이유는 무엇인가요?
// A3. 해당 함수가 users 데이터를 변경하지 않고,
//     읽기만 하기 때문입니다.

// Q4. addUser는 왜 const가 아닌가요?
// A4. 새로운 데이터를 추가해서 vector를 변경하기 때문에
//     객체 상태가 바뀌므로 const를 붙일 수 없습니다.

// Q5. hasUser 함수는 어떤 상황에서 사용되나요?
// A5. 존재하지 않는 사용자 ID로 평점을 입력하는 것을 막기 위해 사용됩니다.

// Q6. UserManager의 역할은 무엇인가요?
// A6. 사용자 데이터를 저장하고,
//     추가 및 조회 기능을 제공하는 관리 클래스입니다.
*/