#pragma once

#include "Rating.h"
#include <vector>

class SimilarityCalculator {
public:
    static int calculate(
        const std::vector<Rating>& user1,
        const std::vector<Rating>& user2
    );
};