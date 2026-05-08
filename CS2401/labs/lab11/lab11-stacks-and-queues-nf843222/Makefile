CC=g++ -Wall -std=c++11

make_lab: lab11main.cc queue.h queue.cc stack.h stack.cc
	$(CC) lab11main.cc queue.cc stack.cc -o lab.out
	
gdb: lab11main.cc queue.h queue.cc stack.h stack.cc
	$(CC) -g lab11main.cc queue.cc stack.cc -o lab_gdb.out

test: run_tests
tests: run_tests
run_test: run_tests
run_tests: _TEST/TEST_cases.cc queue.h queue.cc stack.h stack.cc
	$(CC) _TEST/TEST_cases.cc queue.cc stack.cc -o ./_TEST/test.out
	./_TEST/test.out

clean:
	rm -f _TEST/*.out
	rm -f *.out