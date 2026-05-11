CXX=g++
#
# ALSO look in this directory for include files (needed on MacOS)
INCLUDES=-I/opt/local/include
# Ignore these deprecated feature warnings
IGNORES=-Wno-deprecated-declarations -Wno-maybe-uninitialized
#
CPPFLAGS=-Wall -Werror -O2 -fopenmp  ${INCLUDES} ${IGNORES}

TARGETS=my_parallel

all: ${TARGETS}


test: my_parallel
	-chmod a+rx ./test.*
	-./test.17
	-./test.39
	-./test.55
	-./test.101
	-./test.1001
	-./test.s.10000
	-./test.s.9837
	-./test.s.10211
	-./test.s.10017
	-./test.s.9978
	-./test.s.improvement
	

clean:
	rm -f $(TARGETS) *.o test.*.myoutput test.*.correct .times
