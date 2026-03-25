#pragma once

class Rating {          //User와 Movie를 연결하는 클래스
private:
    int userId;
    int movieId;
    double score;

public:                 //사용자 id, 영화 id, 점수를 받아서 하나의 평점 객체를 생성
    Rating();
    Rating(int userId, int movieId, double score);

    int getUserId() const;
    int getMovieId() const;
    double getScore() const;

    void display() const;
};

//왜 객체(User, Movie)를 직접 안 넣고 id를 넣었나요?
    //객체를 직접 저장하는 것보다 id를 이용하면 구조가 단순해지고, 객체 간 결합도를 낮출 수 있기 때문에 id로 연결
//Rating을 만들면 Movie 평점이 자동으로 반영되나요?
    //아니요. 현재 구조에서는 Rating은 단순히 기록만 저장하고, Movie의 평점은 addRating 함수를 통해 별도로 반영