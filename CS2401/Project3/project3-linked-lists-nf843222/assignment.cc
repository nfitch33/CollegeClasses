/*************************************************************************
    Implementation file for the Assignment class

	Patricia Lindner    February 2024	OU EECS
*************************************************************************/
#include <iostream>
#include <string>
#include <ctime>
#include "assignment.h"

using namespace std;

Assignment::Assignment(){   // default constructor
    name = "NA";
    course = "NA";
    entered = DateTime();
    due = DateTime();
}

void Assignment::input(istream& ins){
        if(&ins == &cin){
            cout << "Enter the assignment's name: ";
            ins >> ws;
            getline(ins, name);

            cout << "Enter the course for this assignment: ";
            ins >> ws;
            getline(ins, course);

            cout << "Enter the due date and time:\n";
            due.input(ins);

            // If you're reading this assignment in interactively, set the date enter to right now
            DateTime tday;
            tday.make_now();
            entered = tday;
        }
        else{
            ins >> ws;
            getline(ins, name);
            ins >> ws;
            getline(ins, course);
            entered.input(ins);
            due.input(ins);
        }
}

void Assignment::output(ostream& outs)const{
 	if(&outs == &cout){
        outs << "Assignment Name: " << name << endl;
        outs << "         Course: " << course << endl;
        outs << "   Date entered: ";
        entered.output(outs);
        outs << "       Due Date: ";
        due.output(outs);
        outs << endl;
    }
    else{     
        outs << name << endl;
        outs << course << endl;
        entered.output(outs);
        due.output(outs);
    }
}

unsigned Assignment::minutes_til_due()const{
    DateTime now;
    now.make_now();
    // If the due date has passed, return 0, otherwise return the number of minutes until it is due
    return (due.minutes_since_1970() < now.minutes_since_1970()) ? 0 : due.minutes_since_1970() - now.minutes_since_1970();
}

unsigned Assignment::minutes_waiting()const{
    DateTime now;
    now.make_now();
    return now.minutes_since_1970() - entered.minutes_since_1970();
}

void convert_minutes(unsigned minutes){
    //cout << minutes << endl;
    // 60 minutes in an hour * 24 hours in a day = 1440 minutes in a day
 	int days = minutes / 1440;
	minutes %= 1440;

	int hours = minutes / 60;
    minutes %= 60;

    cout << days << " Days, " << hours << " hours, " << minutes << " minutes";
}

// Input and output operarators for those who might want to use them
istream& operator >> (istream& ins, Assignment & ap){
	ap.input(ins);
	return ins;
}

ostream& operator << (ostream& outs, const Assignment& ap){
	ap.output(outs);
	return outs;
}