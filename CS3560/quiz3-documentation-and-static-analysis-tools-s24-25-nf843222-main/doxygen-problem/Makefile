DOXYFILE = Doxyfile
.PHONY: all build clean docs

CXXFLAGS=-Wall -g -std=c++17

all: build

build: argmax-program

argmax-program: main.o argmax.o
	$(CXX) $(LDFLAGS) -o $@ $^

docs:
	@echo "entering docs rule"
	doxygen $(DOXYFILE)
# YOUR ANSWER HERE: write a command generate documentation using doxygen.
# HINT: the command is NOT "doxygen -g Doxyfile" doxygen $(DOXYFILE)
# NOTE: Don't forget to indent your command properly.

clean:
	-$(RM) -f *.o
	-$(RM) -f argmax-program