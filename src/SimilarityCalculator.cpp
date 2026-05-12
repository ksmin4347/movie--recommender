#include "SimilarityCalculator.h"
#include <cstdlib>

int SimilarityCalculator::calculate(
    const std::vector<Rating>& user1,
    const std::vector<Rating>& user2)
{
    int commonCount = 0;
    int scoreDiffSum = 0;

    // 두 사용자의 평점을 모두 비교
    for (const Rating& r1 : user1) {
        for (const Rating& r2 : user2) {

            // 같은 영화라면
            if (r1.getMovieId() == r2.getMovieId()) {

                commonCount++;

                // 평점 차이 누적
                scoreDiffSum += std::abs(
                    r1.getScore() - r2.getScore()
                );
            }
        }
    }

    // 공통 영화가 없는 경우
    if (commonCount == 0) {
        return -100;
    }

    // 유사도 계산
    return commonCount * 10 - scoreDiffSum;
}