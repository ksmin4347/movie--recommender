#include "MovieManager.h"   // 영화 여러 개를 관리하는 MovieManager 클래스를 사용하기 위해 포함
#include "UserManager.h"    // 사용자 여러 명을 관리하는 UserManager 클래스를 사용하기 위해 포함
#include "RatingManager.h"  // 평점 여러 개를 관리하는 RatingManager 클래스를 사용하기 위해 포함
#include <iostream>         // std::cout, std::cin 같은 입출력을 사용하기 위해 포함
#include <string>           // std::string 문자열 타입을 사용하기 위해 포함

void printMenu() {   // 메뉴 출력만 담당하는 함수. main이 너무 길어지는 것을 막기 위해 분리함
    std::cout << "\n===== Movie Recommender Menu =====" << std::endl;   // 메뉴 제목 출력, \n으로 줄바꿈 후 보기 좋게 구분
    std::cout << "1. 영화 추가" << std::endl;                         // 1번 메뉴 안내
    std::cout << "2. 제목으로 영화 검색" << std::endl;               // 2번 메뉴 안내
    std::cout << "3. 전체 영화 목록 출력" << std::endl;              // 3번 메뉴 안내
    std::cout << "4. 평점순 영화 목록 출력" << std::endl;            // 4번 메뉴 안내
    std::cout << "5. 사용자 추가" << std::endl;                      // 5번 메뉴 안내
    std::cout << "6. 전체 사용자 목록 출력" << std::endl;            // 6번 메뉴 안내
    std::cout << "7. 평점 입력" << std::endl;                        // 7번 메뉴 안내
    std::cout << "8. 특정 영화의 평점 목록 출력" << std::endl;       // 8번 메뉴 안내
    std::cout << "9. 전체 평점 목록 출력" << std::endl;              // 9번 메뉴 안내
    std::cout << "0. 종료" << std::endl;                             // 0번 메뉴 안내
    std::cout << "메뉴 선택: ";                                      // 사용자에게 메뉴 번호 입력 요청
}

int main() {   // 프로그램 시작점. 사용자의 입력을 받아 각 Manager에게 일을 시키는 역할
    MovieManager movieManager;     // 영화 데이터들을 관리하는 객체 생성
    UserManager userManager;       // 사용자 데이터들을 관리하는 객체 생성
    RatingManager ratingManager;   // 평점 데이터들을 관리하는 객체 생성

    int choice;   // 사용자가 선택한 메뉴 번호를 저장할 변수

    do {   // 사용자가 0을 입력할 때까지 메뉴를 반복 실행
        printMenu();          // 메뉴를 화면에 출력
        std::cin >> choice;   // 사용자가 선택한 메뉴 번호 입력받기

        if (choice == 1) {   // 1번: 영화 추가 기능
            int id, year;                 // 영화 ID와 개봉 연도를 저장할 변수
            std::string title, genre;     // 영화 제목과 장르를 저장할 변수

            std::cout << "영화 ID: ";   // 영화 ID 입력 안내
            std::cin >> id;             // 정수형 영화 ID 입력
            std::cin.ignore();          // 앞의 입력 후 버퍼에 남아 있는 개행문자를 제거해서 getline이 바로 끝나는 문제 방지

            std::cout << "영화 제목: ";      // 영화 제목 입력 안내
            std::getline(std::cin, title);   // 공백이 포함될 수 있으므로 getline으로 제목 전체 입력

            std::cout << "장르: ";           // 장르 입력 안내
            std::getline(std::cin, genre);   // 공백이 포함될 수 있으므로 getline으로 장르 전체 입력

            std::cout << "개봉 연도: ";   // 개봉 연도 입력 안내
            std::cin >> year;            // 정수형 개봉 연도 입력

            movieManager.addMovie(id, title, genre, year);   // 입력받은 정보를 이용해 MovieManager에 영화 추가 요청
        }

        else if (choice == 2) {   // 2번: 제목으로 영화 검색
            std::string title;    // 검색할 제목을 저장할 변수
            std::cin.ignore();    // 메뉴 번호 입력 후 남아 있는 개행문자를 제거해서 getline 정상 동작 보장

            std::cout << "검색할 제목: ";      // 검색할 제목 입력 안내
            std::getline(std::cin, title);     // 공백 포함 제목 검색을 위해 getline 사용

            movieManager.searchByTitle(title); // MovieManager에게 해당 제목의 영화 검색 요청
        }

        else if (choice == 3) {   // 3번: 전체 영화 목록 출력
            movieManager.printAllMovies();   // MovieManager가 관리 중인 모든 영화 출력 요청
        }

        else if (choice == 4) {   // 4번: 평점순 영화 목록 출력
            movieManager.printMoviesSortedByRating();   // 평점 기준으로 정렬한 영화 목록 출력 요청
        }

        else if (choice == 5) {   // 5번: 사용자 추가
            int id;                     // 사용자 ID 저장 변수
            std::string name, email;    // 사용자 이름, 이메일 저장 변수

            std::cout << "사용자 ID: ";   // 사용자 ID 입력 안내
            std::cin >> id;             // 사용자 ID 입력
            std::cin.ignore();          // 버퍼에 남은 개행 제거

            std::cout << "이름: ";           // 사용자 이름 입력 안내
            std::getline(std::cin, name);    // 공백 포함 이름 입력 가능하도록 getline 사용

            std::cout << "이메일: ";          // 이메일 입력 안내
            std::getline(std::cin, email);    // 이메일 입력

            userManager.addUser(id, name, email);   // UserManager에 사용자 추가 요청
        }

        else if (choice == 6) {   // 6번: 전체 사용자 목록 출력
            userManager.printAllUsers();   // UserManager가 관리 중인 모든 사용자 출력 요청
        }

        else if (choice == 7) {   // 7번: 평점 입력
            int userId, movieId;   // 평점을 남기는 사용자 ID와 영화 ID 저장 변수
            double score;          // 평점 점수를 저장할 변수

            std::cout << "사용자 ID: ";   // 사용자 ID 입력 안내
            std::cin >> userId;           // 사용자 ID 입력
            std::cout << "영화 ID: ";     // 영화 ID 입력 안내
            std::cin >> movieId;          // 영화 ID 입력
            std::cout << "평점: ";        // 평점 입력 안내
            std::cin >> score;            // 평점 입력

            if (!userManager.hasUser(userId)) {   // 입력한 사용자 ID가 실제 존재하는지 먼저 확인
                std::cout << "존재하지 않는 사용자 ID입니다." << std::endl;   // 존재하지 않으면 오류 메시지 출력
                continue;   // 현재 반복을 중단하고 다시 메뉴로 돌아감
            }

            if (!movieManager.hasMovie(movieId)) {   // 입력한 영화 ID가 실제 존재하는지 확인
                std::cout << "존재하지 않는 영화 ID입니다." << std::endl;   // 존재하지 않으면 오류 메시지 출력
                continue;   // 현재 반복 중단 후 메뉴로 복귀
            }

            if (score < 0.0 || score > 5.0) {   // 평점이 0.0~5.0 범위를 벗어나는지 검사
                std::cout << "평점은 0.0 이상 5.0 이하만 입력할 수 있습니다." << std::endl;   // 잘못된 점수 입력 알림
                continue;   // 잘못된 평점이면 저장하지 않고 메뉴로 돌아감
            }

            ratingManager.addRating(userId, movieId, score);   // RatingManager에 개별 평점 기록 저장
            movieManager.addRatingToMovie(movieId, score);     // MovieManager에도 해당 영화의 총 평점/평균 계산을 위해 반영

            std::cout << "평점이 정상적으로 입력되었습니다." << std::endl;   // 평점 입력 성공 메시지 출력
        }

        else if (choice == 8) {   // 8번: 특정 영화의 평점 목록 출력
            int movieId;   // 조회할 영화 ID 저장 변수
            std::cout << "영화 ID 입력: ";   // 영화 ID 입력 안내
            std::cin >> movieId;            // 영화 ID 입력

            ratingManager.printRatingsByMovie(movieId);   // 해당 영화의 평점 목록 출력 요청
        }

        else if (choice == 9) {   // 9번: 전체 평점 목록 출력
            ratingManager.printAllRatings();   // 저장된 모든 평점 출력 요청
        }

        else if (choice == 0) {   // 0번: 프로그램 종료
            std::cout << "프로그램을 종료합니다." << std::endl;   // 종료 안내 메시지 출력
        }

        else {   // 0~9 이외의 번호를 입력한 경우
            std::cout << "잘못된 메뉴입니다." << std::endl;   // 잘못된 입력 안내
        }

    } while (choice != 0);   // choice가 0이 아닐 동안 계속 반복해서 메뉴 실행

    return 0;   // 프로그램 정상 종료를 운영체제에 알림
}

/*
========================
main.cpp 예상 질문 & 답변
========================

// Q1. 왜 main에서 모든 기능을 직접 구현하지 않고 Manager 클래스로 나눴나요?
// A1. main은 사용자 입력과 메뉴 제어만 담당하고,
//     실제 데이터 저장, 검색, 출력 같은 기능은 각 Manager 클래스가 맡도록 역할을 분리했습니다.
//     이렇게 하면 코드가 더 깔끔해지고, 기능별 책임이 명확해져서 유지보수가 쉬워집니다.

// Q2. printMenu() 함수를 따로 만든 이유는 무엇인가요?
// A2. 메뉴 출력 코드를 main 안에 계속 쓰면 main 함수가 너무 길어지고 가독성이 떨어집니다.
//     그래서 메뉴 출력만 별도 함수로 분리해 main의 구조를 단순하게 만들었습니다.

// Q3. main에서 MovieManager, UserManager, RatingManager 객체를 왜 생성하나요?
// A3. 영화, 사용자, 평점 데이터를 각각 따로 관리해야 하기 때문입니다.
//     각 Manager 객체는 여러 개의 데이터를 저장하고 관련 기능을 수행하는 역할을 합니다.

// Q4. 평점 입력 시 왜 userManager.hasUser(userId)를 먼저 검사하나요?
// A4. 존재하지 않는 사용자가 평점을 남기는 것은 잘못된 데이터이기 때문입니다.
//     먼저 사용자 존재 여부를 확인해서 잘못된 입력을 막는 방어적 프로그래밍을 적용했습니다.

// Q5. 평점 입력 시 왜 movieManager.hasMovie(movieId)도 검사하나요?
// A5. 존재하지 않는 영화에 평점을 저장하면 데이터의 일관성이 깨지기 때문입니다.
//     실제 존재하는 영화에만 평점을 부여하도록 하기 위해 검사했습니다.

// Q6. 왜 score 범위를 0.0 이상 5.0 이하로 검사하나요?
// A6. 영화 평점의 유효 범위를 제한하기 위해서입니다.
//     잘못된 값이 저장되면 평균 평점 계산이 틀어질 수 있으므로 입력 단계에서 막았습니다.

// Q7. 왜 평점을 RatingManager와 MovieManager 둘 다에 반영하나요?
// A7. RatingManager는 "누가 어떤 영화에 몇 점을 줬는지" 개별 평점 기록을 저장합니다.
//     MovieManager는 영화 자체의 평균 평점 계산을 위해 해당 영화의 총합과 개수를 갱신합니다.
//     즉 하나는 기록 저장, 하나는 통계 반영 역할입니다.

// Q8. std::cin.ignore()를 쓴 이유는 무엇인가요?
// A8. cin >> 로 정수 입력을 받은 뒤 버퍼에 남는 개행문자를 제거하기 위해 사용했습니다.
//     이를 하지 않으면 바로 다음 getline()이 빈 문자열을 읽어버릴 수 있습니다.

// Q9. title, genre, name, email 입력에서 getline()을 쓴 이유는 무엇인가요?
// A9. 공백이 포함된 문자열 전체를 입력받기 위해서입니다.
//     cin >> 는 공백 전까지만 읽지만 getline()은 한 줄 전체를 읽을 수 있습니다.

// Q10. do-while 문을 사용한 이유는 무엇인가요?
// A10. 메뉴는 최소 한 번은 반드시 출력되어야 하므로,
//      먼저 실행하고 나중에 조건을 검사하는 do-while 문이 적절하다고 판단했습니다.

// Q11. continue를 사용한 이유는 무엇인가요?
// A11. 잘못된 사용자 ID, 영화 ID, 평점이 들어왔을 때
//      그 아래 코드를 실행하지 않고 바로 다음 메뉴 반복으로 넘어가기 위해 사용했습니다.
//      이렇게 하면 잘못된 데이터 저장을 방지할 수 있습니다.

// Q12. 이 파일의 역할은 무엇인가요?
// A12. 이 파일은 프로그램의 시작점이며,
//      사용자와 상호작용하면서 입력을 받고 적절한 Manager에게 기능 수행을 요청하는 제어 역할을 합니다.
//      즉 전체 프로그램의 흐름을 관리하는 파일입니다.
*/