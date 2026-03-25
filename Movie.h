#pragma once    //헤더파일이 중복 포함되는 것을 막기위함
#include <string>   //std::string을 쓰기 위함
//영화 한 개를 표현하는 클래스의 선언부
class Movie {
private:            //데이터를 보호하고, 외부에서 수정하지 못하게 하여 안전하게 관리하기 위해 캡슐화
    int         id;
    std::string title;
    std::string genre;
    int         releaseYear;
    double      totalRating;    // averageRating 제거
    int         ratingCount;    // 추가

public:
    Movie();                    // 기본 생성자 추가
    Movie(int id, const std::string& title,
          const std::string& genre, int year);  //영화번호, 제목, 장르, 개봉연도를 받아서 객체를 한번에 초기화하기 위한 생성자

    int         getId()              const;
    std::string getTitle()           const;
    std::string getGenre()           const;
    int         getReleaseYear()     const;  // getYear → getReleaseYear
    double      getAverageRating()   const;  // getRating → getAverageRating
    int         getRatingCount()     const;  // 추가

    void addRating(double r);               // 추가
    void display()               const;     //const 붙은 이유: 출력만 하고 객체 상태 안바꿈
};

//왜 averageRating을 안 쓰고 totalRating + ratingCount를 쓰냐?
    //평균값만 저장하는 것보다 총합과 개수를 저장하면 새로운 평점이 들어올 때 평균을 계산하기 더 편하고 정확함
//왜 기본 생성자를 만들었나?
    //빈 객체를 만들 수 있게 하고, 멤버 변수들을 안전한 기본값으로 초기화하기 위함
//왜 const std::string&를 썼냐
    //문자열을 복사하지 않고 참조로 받아서 효율성을 높이고, 수정하지 않도록 const를 붙임.
//왜 getter에 const가 붙어 있냐
    //getter 함수는 값을 읽기만 하고 객체의 상태를 바꾸지 않기 때문에 const를 붙임.
//평점이 하나도 없으면 평균은 어떻게 되나요?
    //평점 개수가 0일 때는 0으로 나누는 문제가 생기므로, getAverageRating()에서 예외적으로 0.0을 반환하도록 구현
