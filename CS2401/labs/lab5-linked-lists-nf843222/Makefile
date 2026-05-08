CC=g++ -Wall -std=c++11

make_lab: main.cc list.h
	$(CC) main.cc -o lab.out
	
gdb: main.cc list.h
	$(CC) -g main.cc -o lab_gdb.out

test: run_tests
tests: run_tests
run_test: run_tests
run_tests: list.h _TEST/TEST_cases.cc
	$(CC) _TEST/TEST_cases.cc -o ./_TEST/test.out
	./_TEST/test.out

valgrind: list.h _TEST/TEST_cases.cc
	$(CC) -g _TEST/TEST_cases.cc -o ./_TEST/test.out
	valgrind ./_TEST/test.out

clean:
	rm -f _TEST/*.out
	rm -f *.out