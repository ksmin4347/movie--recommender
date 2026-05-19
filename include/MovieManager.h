#pragma once

#include "BaseManager.h"
#include "Movie.h"
#include "Rating.h"
#include <vector>
#include <string>

class MovieManager : public BaseManager {
private:
    std::vector<Movie> movies;

    void sortMoviesById();

public:
    void addMovie(int id, const std::string& title,
                  const std::string& genre, int year);

    void printAllMovies() const;

    void searchByTitle(const std::string& title) const;

    void printMoviesSortedByRating() const;

    bool hasMovie(int movieId) const;

    bool addRatingToMovie(int movieId, double score);

    const Movie* findById(int movieId) const;

    double calculateGenreSimilarity(
        const std::string& genre,
        const std::vector<Rating>& userRatings
    ) const;

    std::vector<Movie> recommend(
        const std::vector<Rating>& userRatings,
        int n = 5
    ) const;

    void loadFromFile(const std::string& filename) override;
    void saveToFile(const std::string& filename) const override;
    int size() const override;
};