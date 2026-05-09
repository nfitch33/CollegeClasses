# The .PHONY target mark the list of targets
# as none-file.
.PHONY: all build sdist clean

all: build sdist

build: $(split_by)

main.o: main.cpp
	g++ -Wall -g -c main.cpp

split_by.o: split_by.cpp
	g++ -Wall -g -c main.cpp

split-by = main.o split_by.o


ZIP = project-sdist.tar.gz
FOLDER = main.cpp split_by.cpp split_by.hpp Makefile

sdist: $(ZIP)

$(ZIP): $(FOLDER)
	tar -czf $(ZIP) $(FOLDER)

clean:
	rm -f $(split_by)

