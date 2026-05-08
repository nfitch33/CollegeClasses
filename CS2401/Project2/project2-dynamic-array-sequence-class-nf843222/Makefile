 #*********************************************
 #
 #	Makfile for CS2401 Project 2, Instagram
 #	Made by Patricia Lindner
 # 	Updated by Kyle Chiasson
 #	Last updated 2/6/2024
 #	For automatic grading to work, do not change this file.
 #	Students are encouraged to read through to understand project requirements, however.
 #
 # ********************************************

CFLAGS = -Wall -std=c++11
CC = g++

a.out: date.o instafollows.o profile.o main.cc
	$(CC) $(CFLAGS) main.cc  _TEST/date.o _TEST/instafollows.o _TEST/profile.o -o $@

date.o: date.cc date.h
	$(CC) $(CFLAGS) -c $< -o _TEST/$@

instafollows.o: instafollows.cc instafollows.h
	$(CC) $(CFLAGS) -c $< -o _TEST/$@

profile.o: profile.cc profile.h
	$(CC) $(CFLAGS) -c $< -o _TEST/$@

test: run_tests
tests: run_tests
run_test: run_tests
run_tests: date.o instafollows.o profile.o
	$(CC) $(CFLAGS) _TEST/TEST_cases.cc _TEST/date.o _TEST/instafollows.o _TEST/profile.o -o _TEST/run_tests
	./_TEST/run_tests

debug: gdb.out
gdb.out: date.o instafollows.o profile.o main.cc
	$(CC) $(CFLAGS) -g main.cc  _TEST/date.o _TEST/instafollows.o _TEST/profile.o -o $@

#note: this test requires the installation of valgrind
valgrind: date.o instafollows.o profile.o
	$(CC) $(CFLAGS) -g _TEST/TEST_cases.cc _TEST/date.o _TEST/instafollows.o _TEST/profile.o -o _TEST/run_tests
	valgrind -s ./_TEST/run_tests

clean:
	rm -f _TEST/*.o *.out _TEST/run_tests
