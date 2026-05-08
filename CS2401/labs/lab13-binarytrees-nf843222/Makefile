CC=g++ -Wall -std=c++11

make_lab: lab13main.cc btreelab.cc btreelab.h
	$(CC) lab13main.cc btreelab.cc -o lab.out
	
gdb: lab13main.cc btreelab.cc btreelab.h
	$(CC) -g lab13main.cc btreelab.cc -o lab_gdb.out

test: run_tests
tests: run_tests
run_test: run_tests
run_tests: btreelab.cc btreelab.h _TEST/TEST_cases.cc
	$(CC) _TEST/TEST_cases.cc btreelab.cc -o ./_TEST/test.out
	./_TEST/test.out

clean:
	rm -f _TEST/*.out
	rm -f *.out