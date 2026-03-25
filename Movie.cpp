#include "Movie.h"
#include <iostream>

// 기본 생성자
Movie::Movie()
    : id(0), releaseYear(0),
      totalRating(0.0), ratingCount(0) {}       //값 없어도 호출되는 생성자

// 4인자 생성자
Movie::Movie(int id, const std::string& title,      //값 있으면 호출되는 생성자
             const std::string& genre, int year)    // string을 복사하지 않고, 원본을 참조해서 받고, 수정은 못하게
    : id(id), title(title), genre(genre),
      releaseYear(year),
      totalRating(0.0), ratingCount(0) {}   //초기화 리스트=>멤버 변수를 생성과 동시에 초기화, 성능 면에서도 더 효율적

int         Movie::getId()           const { return id; }   //const: 이 함수가 객체의 상태를 변경하지 않는다는 것을 보장
std::string Movie::getTitle()        const { return title; }
std::string Movie::getGenre()        const { return genre; }
int         Movie::getReleaseYear()  const { return releaseYear; }
int         Movie::getRatingCount()  const { return ratingCount; }

double Movie::getAverageRating() const {    // 멤버함수를 클래스 외부에 정의
    if (ratingCount == 0) return 0.0;   // 0 나눗셈 방어
    return totalRating / ratingCount;
}

void Movie::addRating(double r) {
    if (r < 0.0 || r > 5.0) return;    // 유효성 검사: 평점을 추가할 때 총합과 개수를 함께 관리해야 함
    totalRating += r;
    ratingCount++;
}

void Movie::display() const {          // 중복 제거, 하나만 유지
    std::cout << id << ". " << title
              << " [" << genre << "]"
              << " (" << releaseYear << ")"
              << "  평점: " << getAverageRating()
              << " (" << ratingCount << "건)"
              << std::endl;
}

//id(id)에서 앞뒤 id는 뭐가 다른가요?
    //앞의 id는 클래스의 멤버 변수이고, 뒤의 id는 생성자의 매개변수
//왜 getter를 사용했나요?
    //멤버 변수를 private으로 보호하고, 외부에서는 함수로만 접근하도록 하기 위함
//이 클래스의 핵심 기능은 무엇인가요?
    //영화 정보를 저장하고, 평점을 추가하며, 평균 평점을 계산하고 출력하는 기능
