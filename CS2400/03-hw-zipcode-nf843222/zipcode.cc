/**
 *   @file: zipcode.cc
 * @author: Nathaniel Fitch
 *   @date: 10/05/2023
 *  @brief: the following program will have the user input their zip code, and the program will spit back a Bar code based off the digits in the Zip code. 
 *          and a remainder number bar code
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
using namespace std;

int getCheckDigitValue (string code);  // Lines 15-19 Are all functions in the program.
string getBarCode (string code);
string getBarCodeRem (int value);
bool checkzip(string code);
bool tryAgain(int value);

int main() {
    int x = 1;
    while (x == 1) { 
    string zipcode; // Lines 24-26 are variable names that are used.
    int rem;
    string bar;
    cout << "Put in your zipcode: " << endl;
    cin >> zipcode;                             // Gets zipcode from user then checks to make sure it is a viable zipcode using lines 29-37 and their corresonding functions.
    while (checkzip(zipcode) == false) {
        if (tryAgain(0) == true) {
            cout << "Put in your zipcode: " << endl;
            cin >> zipcode;
        }
        else {
            return(0);
        }
    }
        rem = getCheckDigitValue(zipcode); // Gets remainder number from the zipcode
        getBarCode(zipcode);               // Gets bar code from original zipcode
        bar = getBarCodeRem(rem);          // Gets bar code from remainder number

        cout << setw(5) << zipcode.at(0);  // Prints the first digit of the zipcode, this one had width 5 instead of 6 -- that is why its outside of the for loop below it.
        
        for (int y = 1; y < 5; y++) {               // prints the other digits of the zipcode 6 lengths apart, so they are below their corresponding bar codes.
            cout << setw(6) << zipcode.at(y);
        }
        cout << setw(6) << rem << endl;         // prints the remainder digit below its bar code.
        if (tryAgain(0) == false) {         // Checks to see if user wants to run program again.
            return(0);
        }
    }
}
bool checkzip(string zipcode) {             // Checks to see if zipcode is too short, long, and if all the digits are numbers.
    if (zipcode.length() < 5) {             // Too short
        cout << "Zipcode needs 5 digits" << endl;
        return false ;
    }
    else if (zipcode.length() > 5) {          // Too long
        cout << "Zipcode has too many digits" << endl;
        return false ;
    }
    else {                                                            // I used a lot of if statements, because using a for or while loop, if one digit was True,
        if ((zipcode.at(0) >= 48) && zipcode.at(0) <= 57) {           // it would print them all as true and it would use all ascii table values, not just numbers.
            if ((zipcode.at(1) >= 48 && (zipcode.at(1) <= 57))) {
                if ((zipcode.at(2) >= 48) && (zipcode.at(2) <= 57)) {
                    if ((zipcode.at(3) >= 48) && (zipcode.at(3) <= 57)){
                        if ((zipcode.at(4) >= 48) && (zipcode.at(4) <= 57)) {
                            return true;
                        }
                        else {
                            return false;
                        }
                    }
                    else {
                        return false;
                    }
                }
                else {
                    return false;
                }
            }
            else {
                return false;
            }
    }
    }
}

bool tryAgain(int value) {                                      // Function that checks if user wants to run the program again.
    string answer;
    cout << "Would you like to try again? (y/n) " << endl;
    cin >> answer;
    if (answer.at(0) == 'y' || answer.at(0) == 'Y') {
        return true;
    }
    else {
        return (0);
    }
}

string getBarCode(string zip) {         // gets bar code for each of the zipcode numbers, as it goes on, adds onto the previous number. BAR = BAR + NEWBAR :: Lines 101-138
    string BAR = "";
    for (int x = 0; x < 5; x++) {
        if (zip.at(x) == '0') {
            BAR = BAR + "||::: ";
        }
        else if (zip.at(x) == '1') {
            BAR = BAR + ":::|| ";
        }
        else if (zip.at(x) == '2') {
            BAR = BAR + "::|:| ";
        }
        else if (zip.at(x) == '3') {
            BAR = BAR + "::||: ";
        }
        else if (zip.at(x) == '4') {
            BAR = BAR + ":|::| ";
        }
        else if (zip.at(x) == '5') {
            BAR = BAR + ":|:|: ";
        }
        else if (zip.at(x) == '6') {
            BAR = BAR + ":||:: ";
        }
        else if (zip.at(x) == '7') {
            BAR = BAR + "|:::| ";
        }
        else if (zip.at(x) == '8') {
            BAR = BAR + "|::|: ";
        }
        else if (zip.at(x) == '9') {
            BAR = BAR + "|:|:: ";
        } 
        else {                      // Is not used in the program, was checking to make sure values were correct.
            BAR = "3";
        }
    }
    cout << "| " << BAR;            // Starts the bar with a line
}
    string getBarCodeRem(int rem) {     // Gets bar code of the remainder digit. Lines 140-173
    string BAR = "";
        if (rem == 0) {
            BAR =  "||::: ";
        }
        else if (rem == 1) {
            BAR = ":::|| ";
        }
        else if (rem  == 2) {
            BAR = "::|:| ";
        }
        else if (rem == 3) {
            BAR =  "::||: ";
        }
        else if (rem == 4) {
            BAR = ":|::| ";
        }
        else if (rem == 5) {
            BAR =  ":|:|: ";
        }
        else if (rem == 6) {
            BAR = ":||:: ";
        }
        else if (rem == 7) {
            BAR =  "|:::| ";
        }
        else if (rem == 8) {
            BAR = "|::|: ";
        }
        else {
            BAR = "|:|:: ";
        }  
        cout << BAR << "|" << endl;         // Starts the bar with a line.
    }
int getCheckDigitValue(string zipcode) {    // Gets the remainder number from the zipcode.
    int rem = 0;
    for (int x = 0; x < 5; x++) {
        rem += (zipcode.at(x) - 48);        // Ascii table values 0=48 9=57, so had to subtract by 48 to get integer digits for remainder integer.
    }
    rem = rem % 10;                         // Print off the remainder digit needed to complete 10
    rem = 10 - rem;                         // 10 - current remainder to get the true remainder needed in the program

    return rem;                             // Returns remainder
}
