#include "User.h"      // User 클래스 선언을 사용하기 위해 포함
#include <iostream>    // std::cout, std::endl 출력 기능 사용

User::User() : id(0) {}
// 기본 생성자
// id를 0으로 초기화
// name, email은 std::string이므로 자동으로 "" (빈 문자열)로 초기화됨

User::User(int id, const std::string& name, const std::string& email)
    : id(id), name(name), email(email) {}
// 매개변수 생성자
// 사용자 ID, 이름, 이메일을 받아 객체 생성
// 초기화 리스트를 사용해서 멤버변수 초기화 (C++ 권장 방식)

int User::getId() const { return id; }
// 사용자 ID 반환
// 객체 상태를 변경하지 않으므로 const

std::string User::getName() const { return name; }
// 사용자 이름 반환
// 읽기 전용 함수이므로 const

std::string User::getEmail() const { return email; }
// 사용자 이메일 반환
// 객체 상태를 변경하지 않으므로 const

void User::display() const {
    std::cout << *this << std::endl;
}
// User 객체를 출력하는 함수
// 실제 출력 형식은 operator<<에 맡기고,
// display()는 출력 요청만 담당

std::ostream& operator<<(std::ostream& os, const User& user) {  //os: 출력 스트림 객체, cout이 전달
    // User 객체를 cout으로 출력하기 위한 연산자 오버로딩

    os << user.getId() << " " << user.getName() << " " << user.getEmail();
    // 사용자 ID, 이름, 이메일을 한 줄로 출력

    return os;
    // ostream을 반환해야 cout << user << endl 같은 연쇄 출력 가능
}

/*
========================
User.cpp 예상 질문 & 답변
========================

// Q1. 기본 생성자는 왜 만들었나요?
// A1. 매개변수 없이 User 객체를 생성할 경우를 대비하기 위해 만들었습니다.
//     또한 id를 0으로 초기화하여 쓰레기값을 방지했습니다.

// Q2. 생성자에서 왜 초기화 리스트를 사용했나요?
// A2. 멤버변수를 객체 생성 시 바로 초기화하는 것이 더 효율적이고,
//     C++에서 권장되는 방식이기 때문입니다.

// Q3. getter 함수에 const를 붙인 이유는 무엇인가요?
// A3. 객체 상태를 변경하지 않고 값을 읽기만 하기 때문입니다.
//     const를 붙이면 const 객체에서도 호출할 수 있고 안정성이 높아집니다.

// Q4. display() 함수에서 *this를 사용하는 이유는 무엇인가요?
// A4. 출력 형식을 operator<< 함수에 맡기기 위해서입니다.
//     출력 로직을 한 곳에 모아 유지보수를 쉽게 하기 위함입니다.

// Q5. operator<<는 왜 필요한가요?
// A5. cout << user 형태로 객체를 출력할 수 있도록 하기 위해서입니다.
//     사용자 정의 타입도 기본 타입처럼 출력할 수 있게 합니다.

// Q6. operator<<에서 getter를 사용하는 이유는 무엇인가요?
// A6. private 멤버에 직접 접근하지 않고,
//     캡슐화를 유지하면서 안전하게 값을 가져오기 위해서입니다.

// Q7. User 클래스의 역할은 무엇인가요?
// A7. 사용자 한 명의 정보를 저장하는 데이터 클래스입니다.
//     (ID, 이름, 이메일)
*/