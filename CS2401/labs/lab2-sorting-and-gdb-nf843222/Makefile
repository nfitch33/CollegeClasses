CC=g++ -Wall -std=c++11

# Note: Requires you to make a file with a main function to work properly
make_lab: numlist.cc numlist.h
	$(CC) *.cc -o lab.out
	
gdb: numlist.cc numlist.h
	$(CC) -g *.cc -o lab_gdb.out

test: run_tests
tests: run_tests
run_test: run_tests
run_tests: numlist.cc numlist.h _TEST/TEST_cases.cc
	$(CC) $^ -o ./_TEST/test.out
	./_TEST/test.out

clean:
	rm -f _TEST/*.out
	rm -f *.out