# A simple Makefile for Lloyd Black's CPSC350 Game of Life Project

EXECUTABLE := GameOfLife

SOURCES := *.cpp

INCLUDES := -I ../include
EXT := out
CC := g++

all:
	$(CC) $(INCLUDES) $(SOURCES) -o $(EXECUTABLE).$(EXT)

realclean:
	find . -type f -name "*.o" -exec rm '{}' \;
	find . -type f -name "*.exe" -exec rm '{}' \;
	find . -type f -name "*.out" -exec rm '{}' \;
	find . -type f -name "*.gch" -exec rm '{}' \;

# this line required by make - don't delete
