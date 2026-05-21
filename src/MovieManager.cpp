#include "MovieManager.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <set>
#include <utility>

void MovieManager::sortMoviesById() {           //데이터 추가 순서에 상관없이 id 오름차순 정렬
    std::sort(movies.begin(), movies.end(),
        [](const Movie& a, const Movie& b) {
            return a.getId() < b.getId();
        }
    );
}

void MovieManager::addMovie(int id, const std::string& title,
                            const std::string& genre, int year) {
    for (const Movie& movie : movies) {
        if (movie.getId() == id) {
            std::cout << "이미 존재하는 영화 ID입니다." << std::endl;
            return;
        }
    }

    movies.push_back(Movie(id, title, genre, year));
    sortMoviesById();   //영화 추가 후 ID 순서대로 다시 재정렬

    std::cout << "영화가 추가되었습니다." << std::endl;
}

void MovieManager::printAllMovies() const {     //영화 목록 출력
    if (movies.empty()) {
        std::cout << "등록된 영화가 없습니다." << std::endl;
        return;
    }

    for (const Movie& movie : movies) {
        std::cout << movie << std::endl;
    }
}

void MovieManager::searchByTitle(const std::string& title) const {  //제목이 정확히 같은 영화만 찾음
    bool found = false;

    for (const Movie& movie : movies) {
        if (movie.getTitle() == title) {
            std::cout << movie << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "해당 제목의 영화가 없습니다." << std::endl;
    }
}

void MovieManager::printMoviesSortedByRating() const {
    if (movies.empty()) {
        std::cout << "등록된 영화가 없습니다." << std::endl;
        return;
    }

    std::vector<Movie> sortedMovies = movies;
    std::sort(sortedMovies.begin(), sortedMovies.end());    //원본을 복사하여 정렬함. csv 파일은 수정X

    for (const Movie& movie : sortedMovies) {
        std::cout << movie << std::endl;
    }
}

bool MovieManager::hasMovie(int movieId) const {    //해당 movieId가 있는지 확인, 평점 입력 전에 사용
    for (const Movie& movie : movies) {
        if (movie.getId() == movieId) {
            return true;
        }
    }

    return false;
}

bool MovieManager::addRatingToMovie(int movieId, double score) {    //특정 영화의 평균 평점 계산에 평점을 반영
    for (Movie& movie : movies) {
        if (movie.getId() == movieId) {
            if (score < 0.0 || score > 5.0) {
                return false;
            }

            return movie.addRating(score);
        }
    }

    return false;
}

const Movie* MovieManager::findById(int movieId) const {    //영화 id로 Moive 객체 찾기
    for (const Movie& movie : movies) {            //포인터를 반환하는 이유: 영화를 찾으면 해당 영화의 주소 반환
        if (movie.getId() == movieId) {                                 //못찾으면 nullptr 반환
            return &movie;
        }
    }

    return nullptr;
}

double MovieManager::calculateGenreSimilarity(      //특정 장르를 얼마나 좋아하는지 계산
    const std::string& genre,
    const std::vector<Rating>& userRatings      //사용자가 남긴 평점 목록
) const {
    double scoreSum = 0.0;      //높은 평점들의 합
    int count = 0;              //4.0 이상 영화의 개수

    for (const Rating& rating : userRatings) {
        const Movie* watchedMovie = findById(rating.getMovieId());      //영화 아이디의 주소 반환

        if (watchedMovie == nullptr) {
            continue;
        }

        if (watchedMovie->getGenre() == genre && rating.getScore() >= 4.0) {
            scoreSum += rating.getScore();          //특정 장르의 평점 4.0 이상 평점의 평균
            count++;
        }
    }

    if (count == 0) {
        return 0.0;
    }

    return scoreSum / count;
}

std::vector<Movie> MovieManager::recommend( //사용자의 평점 목록을 기반으로 장르 기반 추천 영화를 상위 n개 반환
    const std::vector<Rating>& userRatings,     //추천 받을 사용자의 평점 목록
    int n
) const {
    std::vector<Movie> result;      //추천 결과를 저장할 벡터

    if (userRatings.empty() || n <= 0) {        //사용자의 평점 비어있으면 빈 결과 반환
        return result;
    }

    std::set<int> watchedMovieIds;      

    for (const Rating& rating : userRatings) {      //이미 본 id를 set에 저장
        watchedMovieIds.insert(rating.getMovieId());
    }

    std::vector<std::pair<Movie, double>> scoredMovies;     //추천 후보 영화와 그 영화의 추천 점수를 한쌍으로 묶음

    for (const Movie& candidate : movies) {     //candidate: 추천 후보가 될 수 있는 영화
        if (watchedMovieIds.find(candidate.getId()) != watchedMovieIds.end()) { //이미 본거면 추천 X
            continue;
        }

        double genreSimilarity = calculateGenreSimilarity(
            candidate.getGenre(),       //후보 영화의 장르를 가져옴
            userRatings 
        );                              //이 사용자가 그 장르를 얼마나 좋아하는지 계산

        if (genreSimilarity <= 0.0) {   //해당 사용자가 그 장르에 대한 평점을 4.0 이상 안줬으면 그 장르는 패스
            continue;
        }

        double finalScore = genreSimilarity * 10.0
                          + candidate.getAverageRating();       //장르 선호도*10 +영화 평균 평점

        scoredMovies.push_back({candidate, finalScore});        //추천 후보 영화와 점수를 묶음쌍으로 저장
    }

    std::sort(scoredMovies.begin(), scoredMovies.end(),         //추천 점수가 높은 순으로 정렬(아까 저장한 묶음)
        [](const std::pair<Movie, double>& a,
           const std::pair<Movie, double>& b) {
            if (a.second == b.second) {                         //a.second: 추천 점수 / a.first는 영화 객체
                return a.first.getId() < b.first.getId();
            }

            return a.second > b.second;
        }                                                  //정렬 기준: 추천 점수 높은 순, 점수 같으면 영화 id순
    );

    int count = std::min(n, static_cast<int>(scoredMovies.size())); //추천 영화가 n개보다 작을 수 있어서 min 사용

    for (int i = 0; i < count; i++) {       //상위 count개만 결과에 넣음
        result.push_back(scoredMovies[i].first);
    }

    return result;  
}

void MovieManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: " << filename << " 파일을 열 수 없습니다." << std::endl;
        return;
    }

    movies.clear(); //첫 줄 헤더 스킵

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {  //한줄씩 읽기
        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line); //콤마 기준 분리
        std::string token;

        int id;
        std::string title;
        std::string genre;
        int releaseYear;

        std::getline(ss, token, ',');
        id = std::stoi(token);  //숫자 변환

        std::getline(ss, title, ',');

        std::getline(ss, genre, ',');

        std::getline(ss, token, ',');
        releaseYear = std::stoi(token);

        movies.push_back(Movie(id, title, genre, releaseYear)); //객체 생성 후 vector에 저장
    }

    sortMoviesById();   //정렬

    file.close();

    std::cout << filename << " 로드 완료: " << movies.size() << "건" << std::endl;
}

void MovieManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: " << filename << " 파일 저장 실패" << std::endl;
        return;
    }

    file << "id,title,genre,releaseYear" << std::endl;

    for (const Movie& movie : movies) {
        file << movie.getId() << ","
             << movie.getTitle() << ","
             << movie.getGenre() << ","
             << movie.getReleaseYear() << std::endl;
    }

    file.close();

    std::cout << filename << " 저장 완료: " << movies.size() << "건" << std::endl;
}

int MovieManager::size() const {        //영화 개수 반환(벡터 안에 들어있는 원소 개수 반환)
    return static_cast<int>(movies.size());
}   //movies.size()는 size_t 타입이라서 BaseManager의 반환형인 int에 맞추기 위해 static_cast<int> 사용