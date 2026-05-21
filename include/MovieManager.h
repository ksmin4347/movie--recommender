#pragma once

#include "BaseManager.h"
#include "Movie.h"
#include "Rating.h"
#include <vector>
#include <string>

class MovieManager : public BaseManager {   //BaseManager를 public으로 상속 받음
private:
    std::vector<Movie> movies;          //영화 수 늘어날 수 있어 크기가 자동으로 늘어나는 vector 사용

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

    void loadFromFile(const std::string& filename) override;    //override: 가상함수를 자식 클래스에서 정확히 재정의 한걸
    void saveToFile(const std::string& filename) const override;            //컴파일러에게 알려주는 키워드. 오타 방지
    int size() const override;
};