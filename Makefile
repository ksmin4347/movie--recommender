CXX      = g++
CXXFLAGS = -std=c++17 -Wall -g		#c++ 17 문법 기준으로, 경고메세지 보여줌, 디버깅 정보 포함
TARGET   = movie_app				#make가 끝나면 생성될 실행파일 
OBJS = main.o Movie.o User.o Rating.o	#만들어질 객체파일

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp Movie.h
	$(CXX) $(CXXFLAGS) -c $<

Movie.o: Movie.cpp Movie.h
	$(CXX) $(CXXFLAGS) -c $<
	
User.o: User.cpp User.h
	$(CXX) $(CXXFLAGS) -c $<

Rating.o: Rating.cpp Rating.h
	$(CXX) $(CXXFLAGS) -c $<

.PHONY: clean run
clean:
	rm -f $(OBJS) $(TARGET)
run: $(TARGET)
	./$(TARGET)

