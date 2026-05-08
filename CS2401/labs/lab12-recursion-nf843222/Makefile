CC=g++ -Wall -std=c++11

make_lab: lab12main.cc recursion.cc recursion.h
	$(CC) lab12main.cc recursion.cc -o lab.out
	
gdb: lab12main.cc recursion.cc recursion.h
	$(CC) -g lab12main.cc recursion.cc -o lab_gdb.out

test: run_tests
tests: run_tests
run_test: run_tests
run_tests: recursion.cc recursion.h _TEST/TEST_cases.cc
	$(CC) _TEST/TEST_cases.cc recursion.cc -o ./_TEST/test.out
	./_TEST/test.out

clean:
	rm -f _TEST/*.out
	rm -f *.out