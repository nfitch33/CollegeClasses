GPP=g++ -std=c++11 -Wall

a.out: main1.cc dnode.h dlist.h dlist.template node_iterator.h node_iterator.template
	$(GPP) main1.cc

swatches:
	$(GPP) swatches.cc main2.cc -o swatches.out

makinghtml: swatches
	./swatches.out > result
	$(GPP) makinghtml.cc swatches.cc -o makinghtml
	./makinghtml result

# require a.out for run_tests to make sure that the program compiles
# before running each test
run_tests: a.out
	./_TEST/create_tests

clean:
	rm -f *.out _TEST/TEST_CASES/test.* _TEST/TEST_CC/test.* _TEST/OUTPUT/test.*.myoutput result result.html makinghtml
