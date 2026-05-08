/**
 *   @file: lab5.cc
 * @author: Nathaniel Fitch
 *   @date: 09/29/2023
 *  @brief: Asks user for temperatures throughout the month, then tells user what the highest and lowest temperatures have been
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

int main(int argc, char const *argv[]) {

    double temperature;
    cout << "First Temperature Recording" << endl;
    cin >> temperature; // Grabs the first temperature recording
    double LOW_TEMP = temperature; // Sets first values
    double HIGH_TEMP = temperature; // sets first values

    while (temperature != -100) { // Waits until user enters -100

        if (temperature < LOW_TEMP) { // Sets lowest temperature if the current one is less than the old one
            LOW_TEMP = temperature;
            cout << "Enter -100 to end the program" << endl;
            cout << setw(4) << " " << "Next temperature recording: "; // Using set width to have indent to see terminal better
            cin >> temperature; // Grabs new temperature
        }
        else if (temperature > HIGH_TEMP) // Sets highest temperature if the current one is more than the old one.
        {
            HIGH_TEMP = temperature;
            cout << "Enter -100 to end the program" << endl;
            cout << setw(4) << " " << "Next temperature recording: "; // Using set width to have indent to see terminal better
            cin >> temperature; // grabs new temperature
        } 
        else {
            cout << "Enter -100 to end the program" << endl;
            cout << setw(4) << " " << "Next temperature recording: "; // Using set width to have indent to see terminal better
            cin >> temperature; // grabs new temperature

        }
    } // Execute below when -100 is typed.
    cout << "The highest temperature recorded for the month of February is: " << fixed << setprecision(1) << HIGH_TEMP << " degrees" << endl; // OUTPUTS Hottest temperature
    cout << "The lowest temperature recorded for the month of February is: " << fixed << setprecision(1) << LOW_TEMP << " degrees" << endl; // OUTPUTS Lowest temperature
}