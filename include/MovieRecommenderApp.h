#pragma once

#include "MovieManager.h"
#include "UserManager.h"
#include "RatingManager.h"
#include "Recommender.h"

class MovieRecommenderApp {
private:
    MovieManager movieManager;
    UserManager userManager;
    RatingManager ratingManager;
    Recommender recommender;

    void clearInputLine();

    void loadData();
    void saveData() const;
    void rebuildMovieRatings();

    void printMenu() const;
    void printStatisticsMenu() const;

    void runMenuLoop();

    void handleAddMovie();
    void handleSearchMovie();
    void handleAddUser();
    void handleAddRating();
    void handlePrintRatingsByMovie();
    void handleSimilarityComparison();
    void handleRecommendation();
    void handleStatisticsMenu();
    void handleGenreFilter();

public:
    MovieRecommenderApp();

    void run();
};