CC = mpicc
CFLAGS = -O2 -Wall

all: hash_cracker

hash_cracker: hash_cracker.c sha256crypt.c
	$(CC) $(CFLAGS) -o hash_cracker hash_cracker.c sha256crypt.c -lm

clean:
	rm -f hash_cracker