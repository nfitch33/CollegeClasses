# Compiler
CC = gcc

# Output program
TARGET = scanner

# Default rule
all: $(TARGET)

# Build scanner
$(TARGET): lex.yy.c
	$(CC) lex.yy.c -o $(TARGET)

# Generate lex file
lex.yy.c: treebuilder.l
	lex treebuilder.l

# Run with test files
run1: $(TARGET)
	./$(TARGET) < input1.txt

run2: $(TARGET)
	./$(TARGET) < input2.txt

run3: $(TARGET)
	./$(TARGET) < input3.txt

# Clean everything
clean:
	rm -f lex.yy.c $(TARGET)