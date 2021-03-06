CXX = g++ -g
LIBGLUT =  -framework OpenGL -framework GLUT
INCLUDE = ./include
LIB_O = ./lib/JLXLCD.o


.PHONY: default

default: ./bin/main.o

./bin/main.o: ./src/main.cpp ./lib/JLXLCD.o
	$(CXX) -I$(INCLUDE) $(LIB_O) $< -o $@ $(LIBGLUT)

./lib/JLXLCD.o: ./src/JLXLCD.cpp ./include/JLXLCD.h
	$(CXX) -I$(INCLUDE) -c $< -o ./lib/JLXLCD.o
