.PHONY: build clean

CXXFLAGS=-Wall -g -std=c++17

build: swatches-program

swatches-program: main.o swatches.o
	$(CXX) $(LDFLAGS) -o $@ $^

clean:
	-$(RM) -f *.o
	-$(RM) -f swatches-program