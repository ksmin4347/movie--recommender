#include "User.h"
#include <iostream>

User::User() : id(0) {}//왜 id만 초기화 함? : std::string은 기본 생성시 자동으로 빈문자열 ""로 초기화

User::User(int id, const std::string& name, const std::string& email)
    : id(id), name(name), email(email) {}

int User::getId() const { return id; }
std::string User::getName() const { return name; }
std::string User::getEmail() const { return email; }

void User::display() const {
    std::cout << id <<" " << name << " " << email << std::endl;
}

//std::endl은 뭐인가요?
    //줄바꿈을 하고 출력 버퍼를 비워주는 역할
//display에서 getId() 안 쓰고 id 직접 쓰는 이유는?
    //같은 클래스 내부에서는 private 멤버에 직접 접근이 가능하기 때문에 getter를 사용하지 않고 바로 접근