#pragma once
#include "Movie.h"
#include <vector>
#include <string>

class MovieManager {
private:
    std::vector<Movie> movies;

public:
    void addMovie(int id, const std::string& title,
                  const std::string& genre, int year);

    void printAllMovies() const;
    void searchByTitle(const std::string& title) const;
    void printMoviesSortedByRating() const;

    bool hasMovie(int movieId) const;
    bool addRatingToMovie(int movieId, double score);
};