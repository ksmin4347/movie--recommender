#pragma once

#include "BaseManager.h"
#include "Movie.h"
#include <vector>
#include <string>

class MovieManager : public BaseManager {
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

    void loadFromFile(const std::string& filename) override;
    void saveToFile(const std::string& filename) const override;
    int size() const override;
};