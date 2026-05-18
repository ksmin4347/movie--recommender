#include "RatingManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

void RatingManager::addRating(int userId, int movieId, double score) {
    // 새로운 평점을 추가하는 함수

    ratings.push_back(Rating(userId, movieId, score));
    // Rating 객체를 생성해서 vector에 추가
    // (누가 어떤 영화에 몇 점을 줬는지 저장)

    std::cout << "평점이 저장되었습니다." << std::endl;
    // 평점 저장 완료 메시지 출력
}

void RatingManager::printAllRatings() const {
    // 전체 평점 목록을 출력하는 함수

    if (ratings.empty()) {
        // vector가 비어있는지 확인
        std::cout << "등록된 평점이 없습니다." << std::endl;
        return;
    }

    for (const Rating& rating : ratings) {
        // 저장된 모든 평점을 하나씩 순회
        std::cout << rating << std::endl;
        // operator<<를 사용해서 Rating 객체 출력
    }
}

void RatingManager::printRatingsByMovie(int movieId) const {
    // 특정 영화에 대한 평점 목록 출력 함수

    bool found = false;
    // 해당 영화의 평점이 존재하는지 확인하기 위한 변수

    for (const Rating& rating : ratings) {
        // 모든 평점을 순회
        if (rating.getMovieId() == movieId) {
            // 해당 영화 ID와 일치하는 평점 찾기
            std::cout << rating << std::endl;
            // 해당 평점 출력
            found = true;
            // 하나라도 찾았음을 표시
        }
    }

    if (!found) {
        // 하나도 찾지 못한 경우
        std::cout << "해당 영화의 평점이 없습니다." << std::endl;
        // 안내 메시지 출력
    }
}

const std::vector<Rating>& RatingManager::getRatings() const {
    return ratings;
}

void RatingManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: " << filename << " 파일을 열 수 없습니다." << std::endl;
        return;
    }

    ratings.clear();

    std::string line;
    std::getline(file, line);   // header skip

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);
        std::string token;

        int userId;
        int movieId;
        double score;

        std::getline(ss, token, ',');
        userId = std::stoi(token);

        std::getline(ss, token, ',');
        movieId = std::stoi(token);

        std::getline(ss, token, ',');
        score = std::stod(token);

        ratings.push_back(Rating(userId, movieId, score));
    }

    file.close();

    std::cout << filename << " 로드 완료: " << ratings.size() << "건" << std::endl;
}

void RatingManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: " << filename << " 파일 저장 실패" << std::endl;
        return;
    }

    file << "userId,movieId,score" << std::endl;

    for (const Rating& rating : ratings) {
        file << rating.getUserId() << ","
             << rating.getMovieId() << ","
             << rating.getScore() << std::endl;
    }

    file.close();

    std::cout << filename << " 저장 완료: " << ratings.size() << "건" << std::endl;
}

int RatingManager::size() const {
    return static_cast<int>(ratings.size());
}
/*
========================
RatingManager.cpp 예상 질문 & 답변
========================

// Q1. RatingManager 클래스는 왜 필요한가요?
// A1. 여러 개의 Rating 객체를 저장하고 관리하기 위해서입니다.
//     평점 데이터를 추가, 조회, 출력하는 기능을 담당합니다.

// Q2. 왜 vector<Rating>을 사용했나요?
// A2. 평점 개수가 동적으로 변하기 때문에,
//     크기가 자동으로 증가하는 vector를 사용했습니다.

// Q3. addRating에서 바로 push_back을 하는 이유는 무엇인가요?
// A3. Rating 객체 하나를 생성해서 vector에 추가하는 것이 가장 간단한 방법이기 때문입니다.
//     (누가 어떤 영화에 몇 점 줬는지 기록)

// Q4. addRating에서 유효성 검사를 안 한 이유는 무엇인가요?
// A4. Rating 클래스 생성자에서 이미 검사를 수행하고,
//     main에서도 입력 검증을 하기 때문에 여기서는 중복 검사를 하지 않았습니다.
//     (단, 방어적으로 추가해도 더 안전한 코드가 됩니다)

// Q5. printAllRatings에서 empty()를 먼저 검사하는 이유는?
// A5. 출력할 데이터가 없을 때 불필요한 반복을 막고,
//     사용자에게 명확한 안내 메시지를 주기 위해서입니다.

// Q6. printRatingsByMovie에서 found 변수를 둔 이유는?
// A6. 해당 영화에 대한 평점이 하나도 없는 경우를 판단해서
//     안내 메시지를 출력하기 위해서입니다.

// Q7. 왜 getMovieId()를 통해 비교하나요?
// A7. Rating 객체는 movieId를 통해 어떤 영화의 평점인지 구분하기 때문입니다.

// Q8. RatingManager와 MovieManager의 차이는 무엇인가요?
// A8.
// - RatingManager → 개별 평점 기록 저장 (누가, 어떤 영화에, 몇 점)
// - MovieManager → 영화 자체 정보 + 평균 평점 관리

// Q9. 왜 Rating을 Movie 안에 넣지 않고 따로 분리했나요?
// A9. 역할 분리를 위해서입니다.
//     Movie는 요약 정보(평균), Rating은 개별 기록을 담당합니다.

// Q10. 이 클래스의 핵심 역할은 무엇인가요?
// A10. 모든 평점 데이터를 저장하고,
//      특정 조건(전체/영화별)에 따라 출력하는 관리 클래스입니다.
*/