/*
 *      Author: Nathaniel Fitch
 *   Date: 09/15/2023
 * Description: Find and change all errors in the program.
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;


int main() {

    double a, b, c;
    double disc;
    cout << "Enter the values for a, b, and c." << endl;
    cin >> a >> b >> c;
    disc = sqrt((b * b) - 4 * a * c);

    double x1; 
    double x2;

    x1 = (-b + disc) / (2 * a);
    x2 = (-b - disc) / (2 * a);
    cout << "x1 = " << x1 << endl;
    cout << "x2 = " << x2 << endl;
    return 0;
}
