#pragma once

namespace AppConstants {
    constexpr double MIN_RATING = 0.0;
    constexpr double MAX_RATING = 5.0;
    constexpr double INVALID_RATING = -1.0;

    constexpr double HIGH_RATING_THRESHOLD = 4.0;

    constexpr double NO_COMMON_MOVIE_SIMILARITY = -100.0;
    constexpr double SIMILARITY_COMMON_MOVIE_WEIGHT = 10.0;

    constexpr double GENRE_SIMILARITY_WEIGHT = 10.0;

    constexpr double EPSILON = 0.000001;

    constexpr int DEFAULT_SIMILAR_USER_COUNT = 3;
    constexpr int DEFAULT_RECOMMENDATION_COUNT = 5;
    constexpr int DEFAULT_TOP_MOVIE_COUNT = 10;

    constexpr int DEFAULT_PROFILE_GENRE_COUNT = 3;
    constexpr int DEFAULT_PROFILE_MOVIE_COUNT = 5;

    constexpr int OUTPUT_PRECISION = 1;
}