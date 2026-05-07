/**
 *   @file: gas_consumption.cc
 * @author: Nathaniel Fitch
 *   @date: 09/13/2023
 *  @brief: Calculates Distance taken in a trip through miles and how many gallons are used.
 */
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

///Constants - don't change
double town_Driving_Miles_Per_Gallon = 22.5;
double highway_Driving_Miles_Per_Gallon = 29.5;

int main(int argc, char const *argv[]) {
    // Gets both Miles driven in Town and Highway: Lines 18-23 //
    double town_Miles;
    cout << "Enter Miles Driven through Town: ";
    cin >> town_Miles;
    double highway_Miles;
    cout << "Enter Miles Driven on Highway: ";
    cin >> highway_Miles;
    
    // Checks to see if invalid values were entered: Lines 26-29 //
    if (town_Miles < 0 || highway_Miles < 0) {
        cout << "Error: Miles driven cannot be less than 0" << endl;
        exit(0);
    }

    // Caculates Gas Consumption: Lines 32-35 //
    double town_gasConsumption;
    double highway_gasConsumption;
    town_gasConsumption = town_Miles / town_Driving_Miles_Per_Gallon;
    highway_gasConsumption = highway_Miles / highway_Driving_Miles_Per_Gallon;

    // Calculates Totals, Miles and Gallons of Gas: Lines 38-41 //
    double total_Miles;
    double total_gasConsumption;
    double average_Miles_Per_Gallon;
    total_Miles = town_Miles + highway_Miles;
    total_gasConsumption = town_gasConsumption + highway_gasConsumption;
    average_Miles_Per_Gallon = total_Miles / total_gasConsumption;

    // Shows all outputs (Sentence - number, 1 decimal - variable - label - endl): Lines 44-52 //
    cout << "Miles driven in town: " << fixed << setprecision(1) << town_Miles << " Miles" << endl;
    cout << "Gas Consumption of Driving Through Town: " << fixed << setprecision(1) << town_gasConsumption << " Gallons" << endl;
    cout << "Miles drive on highway: " << fixed << setprecision(1) << highway_Miles << " Miles" << endl;
    cout << "Gas Consumption of Driving on Highway: " << fixed << setprecision(1) << highway_gasConsumption << " Gallons" << endl;
    cout << "Total Miles Driven: " << total_Miles << fixed << setprecision(1) << " Miles" << endl;
    cout << "Total Gas Consumption: " << total_gasConsumption << fixed << setprecision(1) << " Gallons" << endl;

    // checks average Miles per Gallon if value is 0/0 (N/A) //
    if (total_gasConsumption <= 0.0) {
        cout << "No Average Can be Calculated" << endl;
        exit(0);
    }
    // Last Output //
    cout << "Average Miles Per Gallon: " << average_Miles_Per_Gallon << fixed << setprecision(1) << " Miles/Gallon" << endl;

    return 0;
} /// main