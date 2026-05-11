.PHONY: all build clean

CXXFLAGS=-Wall
LDFLAGS=

all: build

build: wormhole-program

wormhole-program: program.o
	$(CXX) $(LDFLAGS) -o $@ $^

clean:
	-$(RM) -f *.o
	-$(RM) -f wormhole-program