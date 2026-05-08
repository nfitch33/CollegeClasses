# Created by: Nasseef Abukamail
# This Makefile will allow you to run tests for the appointment class
#
# Usage:
#    make run_tests_mac
#    mingw32-make run_tests_win
#
#Variables
CC = g++
CFLAGS = -g -Wall -std=c++11

# Linking all the files and run the tests. Use your own header and
# object files.

a.out: appointment.o appointment.h appointment_main.o
	$(CC) $(CFLAGS) appointment.o appointment_main.o -o a.out

appointment.o: appointment.cc appointment.h
	$(CC) -c $(CFLAGS) appointment.cc -o appointment.o

appointment_main.o: appointment_main.cc appointment.h
	$(CC) -c $(CFLAGS) appointment_main.cc -o appointment_main.o

######################################## R U N   T E S T S #############################################
run_tests: appointment.h appointment.o
	head appointment.cc
	$(CC) $(CFLAGS) _TEST/TEST_cases.cc appointment.cc -o _TEST/run_tests ; _TEST/run_tests -sr compact
#########################################################################################################

clean:
	rm -rf _TEST/*.o _TEST/run_tests a.out _TEST/a.out

# ######################################### R U N   T E S T s ###########################################
# run_tests: appointment.h appointment.o
# 	head appointment.cc
# 	$(CC) $(CFLAGS) _TEST/TEST_cases.cc _TEST/appointment.o -o _TEST/a.out && ./_TEST/a.out -sr compact
# #######################################################################################################
