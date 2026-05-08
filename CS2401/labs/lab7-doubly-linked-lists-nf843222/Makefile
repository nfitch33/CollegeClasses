CC=g++ -Wall -std=c++11

make_lab: llist.h lab7main.cc llist.cc
	$(CC) lab7main.cc llist.cc -o lab.out
	
gdb: llist.h lab7main.cc llist.cc
	$(CC) -g lab7main.cc llist.cc -o lab_gdb.out

test: run_tests
tests: run_tests
run_test: run_tests
run_tests: llist.h llist.cc _TEST/TEST_cases.cc
	$(CC) _TEST/TEST_cases.cc llist.cc -o ./_TEST/test.out
	./_TEST/test.out

valgrind: llist.h llist.cc _TEST/TEST_cases.cc
	$(CC) -g _TEST/TEST_cases.cc llist.cc -o ./_TEST/test.out
	valgrind ./_TEST/test.out

clean:
	rm -f _TEST/*.out
	rm -f *.out