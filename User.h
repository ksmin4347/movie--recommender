#pragma once
#include <string>

class User{                     //사용자 한명을 나타내는 설계도
private:                        //외부에서 접근 못하게 캡슐화. 정보 보호용
    int id;
    std::string name;
    std::string email;

public:                 //생성자: 객체 생성할 때 멤버 변수 초기화 하기 위함
    User(); // 기본 생성자: 값 없이 객체 생성, 기본값으로 초기화
    User(int id, const std::string& name, const std::string& email); //사용자 정보를 한번에 받아서 초기화
                                            //const: 문자열을 복사하지 않고 참조하여 효율성 높임, 수정되지 않기 위함
    int getId() const;                      //getter: 멤버 변수가 private이어서 외부에서 값을 안전하게 읽기 위함
    std::string getName() const;            //const: 객체의 상태를 변경하지 않는 함수임을 보장
    std::string getEmail() const;

    void display() const;                   //const: 출력만 하고 객체의 상태를 변경하지 않기 때문.
};                                          //만약 const 안붙이면 어떻게 됨?