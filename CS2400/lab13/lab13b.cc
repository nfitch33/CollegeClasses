/**
 *   @file: lab13b.cc
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

class Tollbooth
{
    public:
        // Default
        Tollbooth();

        // Main Functions
        void payinCar();
        void nopayCar();
        void display(ostream& fileout);
        void termDisplay();

        // helper functions
        double get_money();
        int get_car();

    private:
        // Private
        double money;
        int totalCar;
};

int main(int argc, char const *argv[]) {
    Tollbooth T;
    T.termDisplay();
    char user = 'a';
    while (user != 'q' || user != 'Q'){
        cin >> user;
        if (user == 'p' || user == 'P'){
            T.payinCar();
            T.termDisplay();
        }
        else if (user == 'n' || user == 'N'){
            T.nopayCar();
            T.termDisplay();
        }
        else if (user == 'q' || user == 'Q'){
            T.display(cout);
            return -1;
        }
    }
}
Tollbooth::Tollbooth(){
    money = 0;
    totalCar = 0;
}
void Tollbooth::payinCar(){
    money += 0.5;
    totalCar += 1;
}
void Tollbooth::nopayCar(){
    totalCar += 1;
}
double Tollbooth::get_money(){
    return money;
}
int Tollbooth::get_car(){
    return totalCar;
}
void Tollbooth::display(ostream& fileout){
    fileout << "Total number of cars: " << get_car() << endl;
    fileout << "Total amount collected $" << fixed << setprecision(2) << get_money() << endl;
}
void Tollbooth::termDisplay(){
    cout << "P - paid  " << "N - Not Paid  " << "Q - Quit -> ";
}