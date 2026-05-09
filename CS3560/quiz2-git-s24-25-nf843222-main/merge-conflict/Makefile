.PHONY: all build clean

CXXFLAGS=-Wall -g
LDFLAGS=

all: build

build: calc-fibonacci

calc-fibonacci: main.o
	$(CXX) $(LDFLAGS) $^ -o $@

clean:
	$(RM) *.o