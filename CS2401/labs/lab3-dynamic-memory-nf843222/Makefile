CC=g++ -Wall -std=c++11

# Note: Requires you to make a file with a main function to work properly
make_lab:
	$(CC) *.cc -o lab.out
	
gdb:
	$(CC) -g *.cc -o lab_gdb.out

test: run_tests
tests: run_tests
run_test: run_tests
run_tests: 
	@echo No Tests For This Lab

clean:
	rm -f _TEST/*.out
	rm -f *.out
