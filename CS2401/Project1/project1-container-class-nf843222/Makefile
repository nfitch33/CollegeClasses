 #*********************************************
 #
 #	Makfile for CS2401 Project 1, Plant Nursery
 #	Made by Patricia Lindner
 #	Last updated 1/23/2024
 #	For automatic grading to work, do not change this file.
 #	Students are encouraged to read through to understand project requirements, however.
 #
 # ********************************************

CFLAGS = -Wall -std=c++11
CC = g++

a.out: date.o plantNursery.o plant.o
	$(CC) $(CFLAGS) commented_main.cc  _TEST/date.o _TEST/plantNursery.o _TEST/plant.o -o a.out

finished.out: date.o plantNursery.o plant.o
	$(CC) $(CFLAGS) testing_main.cc  _TEST/date.o _TEST/plantNursery.o _TEST/plant.o -o a.out

date.o: date.cc date.h
	$(CC) $(CFLAGS) -c $< -o _TEST/$@

plantNursery.o: plantNursery.cc plantNursery.h
	$(CC) $(CFLAGS) -c $< -o _TEST/$@

plant.o: plant.cc plant.h
	$(CC) $(CFLAGS) -c $< -o _TEST/$@

test: run_tests
tests: run_tests
run_test: run_tests
run_tests: date.o plantNursery.o plant.o
	$(CC) $(CFLAGS) _TEST/TEST_cases.cc _TEST/date.o _TEST/plantNursery.o _TEST/plant.o -o _TEST/run_tests && ./_TEST/run_tests

clean:
	rm -f _TEST/*.o a.out _TEST/run_tests
