CC=g++ -Wall -std=c++11

make_lab: header_lab6.h main_lab6.cc
	$(CC) main_lab6.cc -o lab.out
	
gdb: header_lab6.h main_lab6.cc
	$(CC) -g main_lab6.cc -o lab_gdb.out

test: run_tests
tests: run_tests
run_test: run_tests
run_tests: header_lab6.h _TEST/TEST_cases.cc
	$(CC) _TEST/TEST_cases.cc -o ./_TEST/test.out
	./_TEST/test.out

valgrind: header_lab6.h _TEST/TEST_cases.cc
	$(CC) -g _TEST/TEST_cases.cc -o ./_TEST/test.out
	valgrind ./_TEST/test.out

clean:
	rm -f _TEST/*.out
	rm -f *.out