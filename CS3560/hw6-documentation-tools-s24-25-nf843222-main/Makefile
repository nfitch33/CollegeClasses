# Tell make that these targets are not files.
.PHONY: all build docs clean

CXXFLAGS=-std=c++17 -g
LDFLAGS=

all: build docs

build: othello-game

othello-game: main.o game.o othello.o
	$(CXX) $(LDFLAGS) -o $@ $^


main.o: main.cpp game.hpp othello.hpp
	$(CXX) $(CXXFLAGS) -c -I./vendors -o $@ $<

docs:
	@echo "entering doc target"
	doxygen Doxyfile
# YOUR ANSWER HERE: write a command generate documentation using doxygen.
# HINT: the command is NOT "doxygen -g Doxyfile"
# NOTE: Don't forget to indent your command properly.

clean:
	@echo "entering clean target"
	-rm -f *.o
	-rm othello-game
