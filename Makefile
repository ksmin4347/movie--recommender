# compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g -Iinclude

# target
TARGET = movie_recommender

# directories
SRCDIR = src
INCDIR = include
OBJDIR = obj

# object files
OBJS = $(OBJDIR)/main.o \
       $(OBJDIR)/MovieRecommenderApp.o \
       $(OBJDIR)/Movie.o \
       $(OBJDIR)/User.o \
       $(OBJDIR)/Rating.o \
       $(OBJDIR)/MovieManager.o \
       $(OBJDIR)/UserManager.o \
       $(OBJDIR)/RatingManager.o \
       $(OBJDIR)/SimilarityCalculator.o \
       $(OBJDIR)/Recommender.o

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/main.o: $(SRCDIR)/main.cpp $(INCDIR)/MovieRecommenderApp.h | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/MovieRecommenderApp.o: $(SRCDIR)/MovieRecommenderApp.cpp $(INCDIR)/MovieRecommenderApp.h $(INCDIR)/MovieManager.h $(INCDIR)/UserManager.h $(INCDIR)/RatingManager.h $(INCDIR)/Recommender.h $(INCDIR)/Constants.h | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/Movie.o: $(SRCDIR)/Movie.cpp $(INCDIR)/Movie.h $(INCDIR)/Constants.h | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/User.o: $(SRCDIR)/User.cpp $(INCDIR)/User.h | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/Rating.o: $(SRCDIR)/Rating.cpp $(INCDIR)/Rating.h $(INCDIR)/Constants.h | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/MovieManager.o: $(SRCDIR)/MovieManager.cpp $(INCDIR)/MovieManager.h $(INCDIR)/Movie.h $(INCDIR)/Rating.h $(INCDIR)/BaseManager.h $(INCDIR)/Constants.h | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/UserManager.o: $(SRCDIR)/UserManager.cpp $(INCDIR)/UserManager.h $(INCDIR)/User.h $(INCDIR)/BaseManager.h | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/RatingManager.o: $(SRCDIR)/RatingManager.cpp $(INCDIR)/RatingManager.h $(INCDIR)/Rating.h $(INCDIR)/BaseManager.h | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/SimilarityCalculator.o: $(SRCDIR)/SimilarityCalculator.cpp $(INCDIR)/SimilarityCalculator.h $(INCDIR)/Rating.h $(INCDIR)/Constants.h | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/Recommender.o: $(SRCDIR)/Recommender.cpp $(INCDIR)/Recommender.h $(INCDIR)/MovieManager.h $(INCDIR)/RatingManager.h $(INCDIR)/SimilarityCalculator.h $(INCDIR)/Constants.h | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean run

clean:
	rm -rf $(OBJDIR) $(TARGET)

run: $(TARGET)
	./$(TARGET)