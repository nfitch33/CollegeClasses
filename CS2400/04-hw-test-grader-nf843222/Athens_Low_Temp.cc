/**
 *   @file: test-grader.cc
 * @author: Nathaniel Fitch
 *   @date: 10/23/2023
 *  @brief: Allows the user to put in information using a file to determine what each student got for answers on an exam and what there score was including letter grade.
 * 			Also the program will state what the average was and who of the students got the best score and what the score was.
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>  // All the include statements
#include <fstream>
using namespace std;

ifstream inStream;
int dailyLow[30];
double average;
string placeholderSTRING; // ALL Global Variables
int placeholderINT;
int placeholderTEMP;

double averageLow(int placeholderINT);
int HIGHESTLow(int placeholderTEMP, int placeholderHIGH);
int LOWESTLow(int placeholderTEMP, int placeholderLOW);

int main(int argc, char const *argv[])
{
    int size = 0;
    inStream.open(argv[1]);
    getline(inStream, placeholderSTRING); // GRABS the first getline to set placeholders for lows and highs
    placeholderTEMP = ((placeholderSTRING.at(0) - 48) * 10) + (placeholderSTRING.at(1) - 48); // Sets the line to an integer
    placeholderINT = placeholderTEMP;
    int placeholderHIGH = placeholderTEMP;
    int placeholderLOW = placeholderTEMP;
    for (int x = 0; x < 29; x++){
        getline(inStream, placeholderSTRING);
        placeholderTEMP = ((placeholderSTRING.at(0) - 48) * 10) + (placeholderSTRING.at(1) - 48); // Rewrits the temporary placeholder
        placeholderINT = placeholderINT + placeholderTEMP; // Adds all temporarys to get ready for average.
        dailyLow [x] = placeholderTEMP;         // Creates the array to store the values
        placeholderHIGH = HIGHESTLow(placeholderTEMP, placeholderHIGH); // Checks if original or new is bigger
        placeholderLOW = LOWESTLow(placeholderTEMP, placeholderLOW); // Checks if original or new is smaller
        size++;
    }
    cout << "Average " << averageLow(placeholderINT) << " Degrees" << endl; // Calculates and prints average
    cout << "Highest " << placeholderHIGH << " Degrees" << endl; // Outputs HIGH
    cout << "Lowest " << placeholderLOW << " Degrees" << endl; // Outputs LOW
}
double averageLow(int placeholderINT){ // Calcuates Average
    double average = placeholderINT / 30;
    return average;
}
int HIGHESTLow(int placeholderTEMP, int placeholderHIGH){ // Calcuates HIGHEST
    int HIGH;
    int SAME = placeholderHIGH;
    if (placeholderTEMP > placeholderHIGH){ // Checks if new is higher
        HIGH = placeholderTEMP;
        return HIGH; // returns new if true
    }
    else {
        return SAME; // returns original HIGH
    }
}
int LOWESTLow(int placeholderTEMP, int placeholderLOW){ // Calculates LOWEST
    int LOW;
    int SAME = placeholderLOW;
    if (placeholderTEMP < placeholderLOW){ // checks if new is lower
        LOW = placeholderTEMP;
        return LOW; // returns new if true
    }
    else {
        return SAME; // returns orignal LOW
    }
}