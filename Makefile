# compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g -Iinclude

# target
TARGET = movie_recommender

# object files
OBJS = src/main.o \
       src/Movie.o \
       src/User.o \
       src/Rating.o \
       src/MovieManager.o \
       src/UserManager.o \
       src/RatingManager.o \
       src/SimilarityCalculator.o

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

src/main.o: src/main.cpp include/MovieManager.h include/UserManager.h include/RatingManager.h include/SimilarityCalculator.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/Movie.o: src/Movie.cpp include/Movie.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/User.o: src/User.cpp include/User.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/Rating.o: src/Rating.cpp include/Rating.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/MovieManager.o: src/MovieManager.cpp include/MovieManager.h include/Movie.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/UserManager.o: src/UserManager.cpp include/UserManager.h include/User.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/RatingManager.o: src/RatingManager.cpp include/RatingManager.h include/Rating.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/SimilarityCalculator.o: src/SimilarityCalculator.cpp include/SimilarityCalculator.h include/Rating.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean run

clean:
	rm -f src/*.o $(TARGET)

run: $(TARGET)
	./$(TARGET)