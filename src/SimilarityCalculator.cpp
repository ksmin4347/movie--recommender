#include "SimilarityCalculator.h"
#include <cmath>

double SimilarityCalculator::calculate(     //사용자 2명의 평점 간 유사도 계산
    const std::vector<Rating>& user1,       //객체 만들 필요 없이 계산만 하면 돼서 static 형식으로 만듦
    const std::vector<Rating>& user2)       //복사 비용을 줄이기 위해 참조(&)로 받음, 수정 안하니까 const
{
    int commonCount = 0;
    double scoreDiffSum = 0.0;

    for (const Rating& r1 : user1) {
        for (const Rating& r2 : user2) {
            if (r1.getMovieId() == r2.getMovieId()) {
                commonCount++;      //공통 영화면 카운트
                scoreDiffSum += std::abs(r1.getScore() - r2.getScore());    //공통 영화의 평점 차(절댓값)
            }
        }
    }

    if (commonCount == 0) {
        return -100.0;
    }

    return commonCount * 10.0 - scoreDiffSum;
}