// The implementation file for the MyTime class
#include "MyTime.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>

using namespace std;

// Constructors
MyTime::MyTime(){
	hours = 0;
	minutes = 0;
}

MyTime::MyTime(int h, int m){
	hours = h;
	minutes = m;
}

// Member and friend functions
void MyTime::Reset(int h, int m){
	hours = h;
	minutes = m;
}

void MyTime::simplify(){
    hours += minutes/60;
	minutes = minutes%60;
}

const MyTime MyTime::operator + (const MyTime& t2){
	MyTime tmp;
    tmp.hours = hours + t2.hours;
	tmp.minutes = minutes + t2.minutes;
	tmp.simplify();
	return tmp;
}

const MyTime MyTime::operator - (const MyTime& t2){
	MyTime tmp;
	tmp.minutes = abs((hours * 60 + minutes) - (t2.hours * 60 + t2.minutes));
	tmp.simplify();
	return tmp;
}

const MyTime MyTime::operator / (int num){
	MyTime tmp;
	tmp.minutes = hours * 60 + minutes;
	tmp.minutes /= num;
	tmp.simplify();
	return tmp;
}

const MyTime MyTime::operator * (int num){
	MyTime tmp;
	tmp.minutes = hours * 60 + minutes;
	tmp.minutes *= num;
	tmp.simplify();
	return tmp;
}

bool MyTime::operator == (const MyTime& t2) const{
	return hours == t2.hours && minutes == t2.minutes;
}

bool MyTime::operator < (const MyTime& t2) const{
	return (hours * 60 + minutes) < (t2.hours * 60 + t2.minutes);
}

bool MyTime::operator <=(const MyTime& t2) const{
	return (hours * 60 + minutes) <= (t2.hours * 60 + t2.minutes);
}

void MyTime::input(istream&ins){
	/* Move the implementation code from the >> operator show below here.
	   Remember that since this function will be a member now, there will not be a t1.

	   The >> operator should now call this function.
	   Remove the friend keyword from the operator in the .h file and move the
	   function prototype to after the class declaration.
	*/
	char junk;
	ins >> hours;
  	ins.get(junk);
	ins >> minutes;
	simplify();
}

void MyTime::output(ostream& outs) const{
	outs << hours << ':' << setw(2) << setfill('0') << minutes;
}


ostream& operator <<(ostream& outs, const MyTime& t1){
	t1.output(outs);
    return outs;
}

istream& operator >> (istream& ins, MyTime& t1){
	t1.input(ins);
	return ins;
}