#pragma once           // 헤더 중복 포함 방지
#include <string>      // std::string 사용
#include <iostream>    // ostream 사용

class User {   // 사용자 한 명의 정보를 표현하는 클래스
private:
    int id;                // 사용자 고유 ID
    std::string name;      // 사용자 이름
    std::string email;     // 사용자 이메일

public:
    User();   // 기본 생성자

    User(int id, const std::string& name, const std::string& email);
    // 매개변수 생성자: 사용자 정보를 받아 객체 생성

    int getId() const;           // ID 반환
    std::string getName() const; // 이름 반환
    std::string getEmail() const;// 이메일 반환

    void display() const;        // 사용자 정보 출력 함수

    friend std::ostream& operator<<(std::ostream& os, const User& user);
    // User 객체를 cout으로 출력하기 위한 연산자 오버로딩
};

/*
========================
User.h 예상 질문 & 답변
========================

// Q1. User 클래스를 만든 이유는 무엇인가요?
// A1. 사용자 정보를 하나의 객체로 묶어 관리하기 위해서입니다.
//     (ID, 이름, 이메일)

// Q2. 멤버변수를 private으로 둔 이유는 무엇인가요?
// A2. 외부에서 직접 접근을 막고,
//     getter를 통해서만 안전하게 접근하도록 하기 위해서입니다.

// Q3. 왜 string을 사용했나요?
// A3. 이름과 이메일은 문자열이기 때문에,
//     C 스타일 배열 대신 std::string을 사용해서 안전하고 편리하게 처리했습니다.

// Q4. getter 함수가 필요한 이유는 무엇인가요?
// A4. private 멤버에 직접 접근할 수 없기 때문에,
//     값을 읽어오기 위한 인터페이스를 제공하기 위해서입니다.

// Q5. display() 함수는 왜 필요한가요?
// A5. 객체의 정보를 출력하는 기능을 클래스 내부에 포함시켜,
//     객체지향적으로 데이터와 기능을 함께 관리하기 위해서입니다.

// Q6. operator<<를 사용하는 이유는 무엇인가요?
// A6. 객체를 cout으로 쉽게 출력할 수 있도록 하기 위해서입니다.
//     출력 형식을 통일하고 코드 중복을 줄일 수 있습니다.

// Q7. 이 클래스의 역할은 무엇인가요?
// A7. 사용자 한 명의 데이터를 표현하는 클래스입니다.
//     즉, User는 가장 기본적인 데이터 단위입니다.
*/