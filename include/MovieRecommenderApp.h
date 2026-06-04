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
    void runMenuLoop();

    void handleAddMovie();
    void handleSearchMovie();
    void handleAddUser();
    void handleAddRating();
    void handlePrintRatingsByMovie();
    void handleSimilarityComparison();
    void handleRecommendation();

public:
    MovieRecommenderApp();

    void run();
};