# Task: Implement this Makefile according to the instructions.

EXEC = money_printer

COUNT = count_words.o
SPLIT = split_by.o
MAIN = main.o

all: $(EXEC)

$(EXEC): $(COUNT) $(SPLIT) $(MAIN)
	g++ $(COUNT) $(SPLIT) $(MAIN) -o $(EXEC)

count_word.o: count_words.cpp
	g++ -Wall -g -c count_words.cpp

split_by.o: split_by.cpp
	g++ -Wall -g -c split_by.cpp

main.o: main.cpp
	g++ -Wall -g -c main.cpp

clean:
	rm -f $(EXEC) $(COUNT) $(SPLIT) $(MAIN)
