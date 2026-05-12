#include "UserManager.h"   // UserManager 클래스 선언 사용
#include <iostream>        // std::cout 출력 기능 사용

void UserManager::addUser(int id, const std::string& name, const std::string& email) {
    // 새로운 사용자를 추가하는 함수

    for (const User& user : users) {   // 현재 저장된 모든 사용자 순회
        if (user.getId() == id) {      // 같은 ID가 있는지 확인
            std::cout << "이미 존재하는 사용자 ID입니다." << std::endl;
            // 중복 ID이면 사용자 추가 불가 메시지 출력
            return;   // 함수 종료
        }
    }

    users.push_back(User(id, name, email));
    // 중복이 없으면 새로운 User 객체 생성 후 vector에 추가

    std::cout << "사용자가 추가되었습니다." << std::endl;
    // 추가 완료 메시지 출력
}

void UserManager::printAllUsers() const {
    // 모든 사용자 목록을 출력하는 함수

    if (users.empty()) {   // vector가 비어있는지 확인
        std::cout << "등록된 사용자가 없습니다." << std::endl;
        return;
    }

    for (const User& user : users) {   // 모든 사용자 순회
        std::cout << user << std::endl;
        // operator<<를 사용해서 User 객체 출력
    }
}

bool UserManager::hasUser(int userId) const {
    // 특정 ID의 사용자가 존재하는지 확인하는 함수

    for (const User& user : users) {   // 모든 사용자 순회
        if (user.getId() == userId) {  // ID가 일치하면
            return true;   // 존재함
        }
    }
    return false;   // 끝까지 없으면 존재하지 않음
}

/*
========================
UserManager.cpp 예상 질문 & 답변
========================

// Q1. UserManager 클래스는 왜 필요한가요?
// A1. 여러 개의 User 객체를 저장하고 관리하기 위해서입니다.
//     사용자 데이터를 추가, 조회, 출력하는 역할을 합니다.

// Q2. users를 private으로 둔 이유는 무엇인가요?
// A2. 외부에서 직접 접근하면 데이터가 임의로 수정될 수 있기 때문에,
//     addUser 같은 함수들을 통해서만 접근하도록 캡슐화를 적용했습니다.

// Q3. addUser에서 중복 ID를 검사하는 이유는 무엇인가요?
// A3. 사용자 ID는 고유값이기 때문에,
//     중복되면 어떤 사용자인지 구분할 수 없어 데이터 무결성이 깨집니다.

// Q4. push_back을 사용하는 이유는 무엇인가요?
// A4. vector에 새로운 User 객체를 추가하기 위해 사용합니다.
//     vector는 동적으로 크기가 증가하는 자료구조입니다.

// Q5. printAllUsers에서 empty()를 먼저 검사하는 이유는 무엇인가요?
// A5. 출력할 데이터가 없을 때 불필요한 반복을 막고,
//     사용자에게 명확한 메시지를 주기 위해서입니다.

// Q6. hasUser 함수는 왜 필요한가요?
// A6. 특정 사용자 ID가 존재하는지 확인하기 위해 사용됩니다.
//     특히 평점 입력 시 존재하지 않는 사용자 입력을 막기 위해 사용됩니다.

// Q7. hasUser 함수에서 const를 붙인 이유는 무엇인가요?
// A7. users 데이터를 변경하지 않고 읽기만 하기 때문입니다.
//     const를 붙여서 함수의 의도를 명확히 했습니다.

// Q8. MovieManager와 UserManager는 어떤 점이 비슷한가요?
// A8. 둘 다 vector로 데이터를 관리하고,
//     추가, 검색, 출력 기능을 제공하는 "관리 클래스"라는 점에서 구조가 동일합니다.

// Q9. 이 클래스의 핵심 역할은 무엇인가요?
// A9. 여러 사용자 데이터를 저장하고,
//     추가 및 존재 여부 확인 기능을 제공하는 관리 클래스입니다.
*/