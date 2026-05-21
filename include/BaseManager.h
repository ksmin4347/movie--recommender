#pragma once

#include <string>
//3개의 순수 가상 함수 존재->부모 클래스에서 선언만 하고, 실제 구현은 자식 클래스가 반드시 하도록 강제하는 함수. 함수 뒤에 =0
class BaseManager {
public:
    virtual void loadFromFile(const std::string& filename) = 0;     //자식클래스들이 무조건 이 함수 구현하게 강제
    virtual void saveToFile(const std::string& filename) const = 0;
    virtual int size() const = 0;

    virtual ~BaseManager() = default;   //소멸자: 객체가 사라질 때 자동으로 호출되는 함수
                                        //default: 소멸자의 동작을 따로 직접 작성하지 않고, 컴파일러가 기본 동작을 만들게 함.
};

/*
1.BaseManager.h 만든 이유
    3개의 매니저 클래스가 모두 파일을 불러오고 저장하는 기능을 가져야하기 때문에 공통 인터페이스를 강제하기 위해 만듦
    각 매니저 클래스에서 override로 구현함
2.virtual이 필요한 이유
    상속관계에서 부모 클래스 포인터로 자식 객체를 다룰 수 있어서 소멸자를 virtual로 두는 것이 안전. 
    그래야 부모 포인터로 삭제하더라도 자식 소멸자가 올바르게 호출
3.BaseManager에서 직접 구현하지 않은 이유
    각 매니저 클래스가 읽는 csv 구조가 달라서 규칙만 강제하고, 실제 구현은 각 매니저 클래스가 담당
*/