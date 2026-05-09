# The .PHONY target mark the list of targets
# as none-file.
.PHONY: all build sdist clean

# __YOUR_ANSWER_HERE__  THANKS HAVING FUN THIS ONE :) ENJOY

# MAIN FILE
THE_SCRIPT = main.o game.o othello.o

# DEBUG
DEBOOGLER = debug_main.o game.o othello.o

# EXECUTABLE
O_THE_SCRIPT = othello-game
O_DEBOOGLER = othello-game-debug

# ALL FILES
FOLDER = colors.hpp debug_main.cpp game.cpp game.hpp main.cpp othello.cpp othello.hpp piece.hpp Makefile

# ZIP FILE (for sdist)
ZIP = othello-sdist.tar.gz

# build and sdist
all: build sdist

# build executables
build: $(O_DEBOOGLER) $(O_THE_SCRIPT)

# build zip folder
sdist: $(ZIP)

$(ZIP): $(FOLDER)
	tar -czf $(ZIP) $(FOLDER)

# executable for othello-game
othello-game: $(THE_SCRIPT)
	g++ $(THE_SCRIPT) -o $(O_THE_SCRIPT)

#creates executable for othello-game-debug
othello-game-debug: $(DEBOOGLER)
	g++ $(DEBOOGLER) -o $(O_DEBOOGLER)

#creates main
main.o: main.cpp
	g++ -Wall -g -c main.cpp

# creates game
game.o: game.cpp
	g++ -Wall -g -c game.cpp

# creates othello
othello.o: othello.cpp
	g++ -Wall -g -c othello.cpp

# creates debug
debug_main.o: debug_main.cpp
	g++ -Wall -g -c debug_main.cpp

clean:
	rm -f $(THE_SCRIPT) $(DEBOOGLER) $(O_THE_SCRIPT) $(O_DEBOOGLER)
