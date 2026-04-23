#include "Movie.h"      // Movie 클래스의 선언을 가져오기 위해 포함
#include <iostream>     // std::cout, std::endl 같은 출력 기능을 사용하기 위해 포함
#include <iomanip>      // std::fixed, std::setprecision 같은 출력 형식 조절 기능을 사용하기 위해 포함

Movie::Movie()   // 기본 생성자: 객체를 아무 값 없이 만들 때 호출됨
    : id(0), releaseYear(0), totalRating(0.0), ratingCount(0) {}  
    // 초기화 리스트를 사용해 id, releaseYear, totalRating, ratingCount를 기본값으로 초기화
    // title과 genre는 std::string이라 따로 쓰지 않아도 빈 문자열로 자동 초기화됨

Movie::Movie(int id, const std::string& title,
             const std::string& genre, int year)   // 매개변수 생성자: 영화 정보를 받아 객체 생성
    : id(id), title(title), genre(genre),
      releaseYear(year), totalRating(0.0), ratingCount(0) {}
    // 전달받은 id, title, genre, year로 멤버변수를 초기화
    // totalRating과 ratingCount는 새 영화이므로 아직 평점이 없어서 0으로 시작

int Movie::getId() const { return id; }  
// 영화의 id를 반환하는 getter 함수
// 멤버변수를 읽기만 하고 객체 상태를 바꾸지 않으므로 const를 붙임

std::string Movie::getTitle() const { return title; }  
// 영화 제목을 반환하는 getter 함수
// 객체를 변경하지 않기 때문에 const 사용

std::string Movie::getGenre() const { return genre; }  
// 영화 장르를 반환하는 getter 함수
// 읽기 전용 함수이므로 const 사용

int Movie::getReleaseYear() const { return releaseYear; }  
// 영화 개봉 연도를 반환하는 getter 함수
// 객체 상태를 바꾸지 않으므로 const 사용

int Movie::getRatingCount() const { return ratingCount; }  
// 현재 이 영화가 받은 평점 개수를 반환하는 getter 함수
// 값을 읽기만 하므로 const 사용

double Movie::getAverageRating() const {   // 평균 평점을 계산해서 반환하는 함수
    if (ratingCount == 0) return 0.0;      // 평점이 하나도 없으면 0으로 나누는 오류를 막기 위해 0.0 반환
    return totalRating / ratingCount;      // 평점 총합을 평점 개수로 나누어 평균 평점 계산
}

bool Movie::addRating(double r) {          // 영화에 평점 하나를 추가하는 함수
    if (r < 0.0 || r > 5.0) return false;  // 평점 범위를 벗어나면 잘못된 입력이므로 false 반환
    totalRating += r;                      // 유효한 평점이면 총합에 더함
    ratingCount++;                         // 평점 개수를 1 증가시킴
    return true;                           // 정상적으로 평점 추가가 끝났음을 알리기 위해 true 반환
}

void Movie::display() const {              // 영화 정보를 화면에 출력하는 함수
    std::cout << *this << std::endl;       // 현재 객체 자신(*this)을 operator<<로 출력
}                                          // 출력 형식을 한 곳(operator<<)에 모아두기 위해 이렇게 작성함

bool Movie::operator==(const Movie& other) const {   // 두 Movie 객체가 같은 영화인지 비교하는 연산자
    return id == other.id;                            // id가 같으면 같은 영화로 판단
}                                                     // 객체 상태를 바꾸지 않으므로 const 사용

bool Movie::operator<(const Movie& other) const {     // 두 Movie 객체의 대소 비교를 정의하는 연산자
    return getAverageRating() > other.getAverageRating();
}  
// 여기서는 평균 평점이 높은 영화가 "앞에 오도록" > 비교를 사용
// 즉, sort()를 하면 일반적인 오름차순이 아니라 평점 높은 순으로 정렬되게 설계한 것

std::ostream& operator<<(std::ostream& os, const Movie& movie) {  
    // Movie 객체를 cout으로 출력할 수 있게 해주는 전역 함수
    // ostream&를 반환해야 cout << a << b 처럼 연쇄 출력(chaining)이 가능함

    os << std::fixed << std::setprecision(1);  
    // 실수 출력 형식을 고정 소수점으로 설정하고 소수점 첫째 자리까지 보이도록 설정
    // 예: 4 -> 4.0, 4.25 -> 4.3

    os << movie.id << ". " << movie.title
       << " [" << movie.genre << "]"
       << " (" << movie.releaseYear << ")"
       << " 평점: " << movie.getAverageRating()
       << " (" << movie.ratingCount << "건)";
    // 영화의 id, 제목, 장르, 개봉연도, 평균평점, 평점 개수를 보기 좋은 형식으로 출력

    return os;  
    // ostream 객체를 다시 반환해서 출력 연산을 이어서 할 수 있게 함
}

/*
========================
Movie.cpp 예상 질문 & 답변
========================

// Q1. 기본 생성자를 왜 만들었나요?
// A1. 객체를 매개변수 없이 생성해야 하는 상황에 대비하기 위해 만들었습니다.
//     또한 멤버변수들을 기본값으로 초기화해서 쓰레기값이 들어가는 것을 방지합니다.

// Q2. 생성자에서 왜 초기화 리스트를 사용했나요?
// A2. 초기화 리스트는 객체가 생성될 때 멤버변수를 바로 초기화하므로
//     생성 후 대입하는 것보다 효율적이고, C++에서 권장되는 방식이기 때문입니다.

// Q3. totalRating와 ratingCount를 0으로 초기화한 이유는 무엇인가요?
// A3. 새로 생성된 영화는 아직 아무도 평점을 주지 않았기 때문입니다.
//     따라서 평점 총합과 평점 개수는 0에서 시작해야 합니다.

// Q4. getter 함수들에 왜 const를 붙였나요?
// A4. getter 함수들은 멤버변수 값을 읽기만 하고 객체 상태를 변경하지 않기 때문입니다.
//     const를 붙이면 const 객체에서도 호출할 수 있고, 실수로 값을 바꾸는 것을 막을 수 있습니다.

// Q5. getAverageRating()에서 ratingCount가 0일 때 0.0을 반환하는 이유는 무엇인가요?
// A5. 평점이 하나도 없을 때 totalRating / ratingCount를 하면 0으로 나누기가 발생하므로,
//     이를 방지하기 위해 먼저 검사해서 0.0을 반환했습니다.

// Q6. addRating() 함수의 반환형을 왜 bool로 했나요?
// A6. 평점 추가가 성공했는지 실패했는지를 호출한 쪽에서 알 수 있게 하기 위해서입니다.
//     범위를 벗어난 잘못된 입력이면 false를 반환하도록 했습니다.

// Q7. addRating()에서 왜 평점 범위를 검사하나요?
// A7. 평점은 0.0 이상 5.0 이하만 유효하다고 정했기 때문입니다.
//     잘못된 값이 들어오면 평균 평점 계산이 틀어질 수 있어서 입력 검증을 했습니다.

// Q8. display() 함수 안에서 왜 그냥 cout을 직접 쓰지 않고 *this를 출력하나요?
// A8. 출력 형식을 operator<< 함수에 모아두면 중복을 줄일 수 있기 때문입니다.
//     display()는 출력 요청만 하고, 실제 형식은 operator<<가 담당하게 역할을 분리했습니다.

// Q9. operator==는 왜 id 기준으로 비교했나요?
// A9. 영화마다 고유한 id를 가진다고 가정했기 때문입니다.
//     제목이 같아도 다른 영화일 수 있지만, id는 중복되지 않는 식별자라서 비교 기준으로 적절하다고 판단했습니다.

// Q10. operator<에서 왜 > 비교를 사용했나요?
// A10. sort()를 했을 때 평균 평점이 높은 영화가 먼저 나오게 하기 위해서입니다.
//      일반적인 오름차순과 반대로, 평점 내림차순 정렬 효과를 주기 위해 >를 사용했습니다.

// Q11. operator<<는 왜 멤버 함수가 아니라 전역 함수인가요?
// A11. cout << movie 형태에서 왼쪽 피연산자는 cout이기 때문입니다.
//      그래서 Movie 클래스의 멤버 함수로 만들기보다 전역 함수로 만드는 것이 자연스럽습니다.

// Q12. operator<<에서 왜 ostream&를 반환하나요?
// A12. cout << movie << endl 처럼 출력 연산을 연속해서 이어가기 위해서입니다.
//      만약 void를 반환하면 연쇄 출력이 불가능해집니다.

// Q13. fixed와 setprecision(1)을 사용한 이유는 무엇인가요?
// A13. 평균 평점을 항상 소수점 첫째 자리까지 일정한 형식으로 출력하기 위해 사용했습니다.
//      예를 들어 4 대신 4.0처럼 보이게 할 수 있습니다.
*/