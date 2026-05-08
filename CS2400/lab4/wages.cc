/**
 *   @file: wages.cc
 * @author: Nathaniel Fitch
 *   @date: 09/22/2023
 *  @brief: Calculates Profit for two scenarios to tell which one is better outcome based off profit in sales vs. normal wage.
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

int main(int argc, char const *argv[]) {
    double dollars_sales;   // Determines all variables needed for program lines 14-23
    cout << "Enter the amount in sales: $";
    cin >> dollars_sales; // User enters sales

    double hours = 40;
    double pay_per_hour = 5.50;
    double wage = hours * pay_per_hour; // Determines normal wage

    double comission1 = 0.10; // Percentages for each plan
    double commision2 = 0.15;

    double sales1 = dollars_sales * comission1; // Determines First Plan sales
    double sales2 = dollars_sales * commision2; // Determines Second Plan sales

    double plan1 = wage + sales1; // Detemines First Plan entirity
    double plan2 = sales2; // Determines Second Plan entirity

    cout << "Amount in sales: $" << dollars_sales << endl;
    cout << "Plan 1 pays: $" << fixed << setprecision(2) << plan1 << endl; // Lines 31-33 Write outputs for user
    cout << "Plan 2 pays: $" << fixed << setprecision(2) << plan2 << endl;

    if (plan1 > plan2) {
        cout << "Plan 1 is better" << endl;
    }                                               // Lines 35-40 Write which plan is better for the user.
    else {
        cout << "Plan 2 is better" << endl;
    }
}