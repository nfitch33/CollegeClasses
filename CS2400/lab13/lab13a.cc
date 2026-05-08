/**
 *   @file: lab13a.cc
 * @author: Nathaniel Fitch
 *   @date: 12/1/2023
 *  @brief: The following project allows the user to send in a text file, that will encrypt the date of birth and social sequrity numbers to astericks.
 *          The names will be set to uppercase only and other characters remain the same.
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <cctype>
using namespace std;

class Counter
{
 public:
    Counter (); //initializes the counter value to 0.
    Counter(int new_val); // value is set according to the
                        // incoming argument.
    void increment(); //increment counter value by 1.
    int get_value(); //returns the value of member
 //variable
 private:
    int value;
} c;

int main(int argc, char const *argv[]) {
    Counter a(6);
    cout << "Number is: " << a.get_value() << endl;
    a.increment();
    cout << "New number is: " << a.get_value() << endl;
}

Counter::Counter(){
    value = 0;
}
Counter::Counter(int new_val){
    value = new_val;
}
void Counter::increment(){
    if (value < 10){
        value += 1;
    }
}
int Counter::get_value(){
    return value;
}