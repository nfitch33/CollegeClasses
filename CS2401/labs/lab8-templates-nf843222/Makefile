CC=g++ -Wall -std=c++11

make_lab: tarray.h lab8main.cc
	$(CC) lab8main.cc -o lab.out
	
gdb: tarray.h lab8main.cc
	$(CC) -g lab8main.cc -o lab_gdb.out

test: run_tests
tests: run_tests
run_test: run_tests
run_tests: tarray.h _TEST/TEST_cases.cc
	$(CC) _TEST/TEST_cases.cc -o ./_TEST/test.out
	./_TEST/test.out

valgrind: tarray.h _TEST/TEST_cases.cc
	$(CC) -g _TEST/TEST_cases.cc -o ./_TEST/test.out
	valgrind ./_TEST/test.out

clean:
	rm -f _TEST/*.out
	rm -f *.out