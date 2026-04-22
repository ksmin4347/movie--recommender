#include "Movie.h"
#include <iostream>
#include <iomanip>

Movie::Movie()
    : id(0), releaseYear(0), totalRating(0.0), ratingCount(0) {}

Movie::Movie(int id, const std::string& title,
             const std::string& genre, int year)
    : id(id), title(title), genre(genre),
      releaseYear(year), totalRating(0.0), ratingCount(0) {}

int Movie::getId() const { return id; }
std::string Movie::getTitle() const { return title; }
std::string Movie::getGenre() const { return genre; }
int Movie::getReleaseYear() const { return releaseYear; }
int Movie::getRatingCount() const { return ratingCount; }

double Movie::getAverageRating() const {
    if (ratingCount == 0) return 0.0;
    return totalRating / ratingCount;
}

bool Movie::addRating(double r) {
    if (r < 0.0 || r > 5.0) return false;
    totalRating += r;
    ratingCount++;
    return true;
}

void Movie::display() const {
    std::cout << *this << std::endl;
}

bool Movie::operator==(const Movie& other) const {
    return id == other.id;
}

bool Movie::operator<(const Movie& other) const {
    return getAverageRating() > other.getAverageRating();
}

std::ostream& operator<<(std::ostream& os, const Movie& movie) {
    os << std::fixed << std::setprecision(1);
    os << movie.id << ". " << movie.title
       << " [" << movie.genre << "]"
       << " (" << movie.releaseYear << ")"
       << " 평점: " << movie.getAverageRating()
       << " (" << movie.ratingCount << "건)";
    return os;
}