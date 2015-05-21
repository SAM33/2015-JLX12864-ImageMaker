CXX = g++ -g
LIBGLUT = -lGL -lGLU -lglut



.PHONY: ./main.o
./main.o: ./main.cpp
	$(CXX) $< -o $@ $(LIBGLUT)
