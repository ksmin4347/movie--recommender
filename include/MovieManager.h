#pragma once

#include "BaseManager.h"
#include "Movie.h"
#include "Rating.h"
#include "Constants.h"
#include <vector>
#include <string>
#include <map>

class MovieManager : public BaseManager {
private:
    std::vector<Movie> movies;

    void sortMoviesById();

    std::string normalizeText(const std::string& text) const;

public:
    void addMovie(int id, const std::string& title,
                  const std::string& genre, int year);

    void printAllMovies() const;

    void searchByTitle(const std::string& title) const;

    void printMoviesSortedByRating() const;

    std::vector<Movie> filterByGenre(const std::string& genre) const;

    void printMoviesByGenre(const std::string& genre) const;

    std::vector<std::string> getAllGenres() const;

    void printAvailableGenres() const;

    double getOverallAverageRating() const;

    std::map<std::string, double> getAverageRatingByGenre() const;

    std::vector<Movie> getTopNMovies(int n) const;

    void printOverallAverageRating() const;

    void printAverageRatingByGenre() const;

    void printTopNMovies(int n) const;

    bool hasMovie(int movieId) const;

    bool addRatingToMovie(int movieId, double score);

    const Movie* findById(int movieId) const;

    double calculateGenreSimilarity(
        const std::string& genre,
        const std::vector<Rating>& userRatings
    ) const;

    std::vector<Movie> recommend(
        const std::vector<Rating>& userRatings,
        int n = AppConstants::DEFAULT_RECOMMENDATION_COUNT
    ) const;

    void loadFromFile(const std::string& filename) override;
    void saveToFile(const std::string& filename) const override;
    int size() const override;
};