/**
 *   @file: agenda_main.cc
 * @author: Nathaniel Fitch
 *   @date: 11/29/2023
 *  @brief: In this project, the assignment is split into 3 files, one for the main for the user, one for the functions, and one for the testing of those functions
 *          The project also used tests for the grade, so we could test it ourseleves, after extensive work... 50/50
 */

#include <iostream>
#include <iomanip>
#include <cstdlib> // All include Statements
#include <vector>
#include <fstream>
#include <cctype>
#include "agenda.h"
using namespace std;

ifstream inStream;
ofstream outStream;

int main(int argc, char const *argv[]) {
    string appData;
    string placeholder;
    string extra;
    string place;
    string counter;
    if (argv[2]){
        place = argv[2];
    }
    else {
        place = "pop";
    }
    if (argv[3]){
        counter = argv[3];
    }
    else{
        counter = "pop";
    }
    inStream.open(argv[1]);
    vector<Appointment> data;
    while (getline(inStream, appData)){
        if (appData != ""){
            Appointment a(appData);
            data.push_back(a);
        }
    }
    if (place == "-ps"){
        cout << setw(55) << setfill('-') << '-' << endl;
        cout << setfill(' ');
        data.at(0).standardOrder(counter, data);
    }
    else if (place == "-p"){
        
        cout << setw(55) << setfill('-') << '-' << endl;
        cout << setfill(' ');
        data.at(0).printMilitary(counter, data);
    }
    else if (place == "-a"){
        cout << setw(55) << setfill('-') << '-' << endl;
        cout << setfill(' ');
        data.at(0).addAppointment(counter, data);
    }
    else if (place == "-dt"){
        cout << setw(55) << setfill('-') << '-' << endl;
        cout << setfill(' ');
        data.at(0).deleteTitle(counter, data);
    }
    else if (place == "-dm"){
        cout << setw(55) << setfill('-') << '-' << endl;
        cout << setfill(' ');
        data.at(0).deleteMilitary(counter, data);
    }
    else {
        cout << "Command was invalid" << endl;
    }
    cout << setfill('-') << setw(55) << '-' << endl;
    cout << setfill(' ');
    cout << "In order by standard time: -ps" << endl;
    cout << "Print all at set military time: -p time" << endl;
    cout << "Add an appointment: -a Appointment Data" << endl;
    cout << "Delete all with certain title: -dt title" << endl;
    cout << "Delete all appointments with certain military time: -dm time" << endl; 
    cout << "Quit: -q" << endl;
    cout << setfill('-') << setw(55) << '-' << endl;
    cout << setfill(' ');
    cout << "Selection: ";
    getline(cin, extra);
    cout << setfill('-') << setw(55) << '-' << endl;
    cout << setfill(' ');

    while (extra != "-q"){
        for (size_t x = 0; x < extra.length(); x++){
            if (extra.at(x) == ' '){
                break;
            }
            else {
                placeholder = placeholder + extra.at(x);
            }
        }
        int y = extra.find(placeholder);
        extra.erase(y, placeholder.length());
        size_t startpos = extra.find_first_not_of(" ");
        size_t lastpos = extra.find_last_not_of(" ");
        if (startpos != string::npos || lastpos != string::npos){
            extra = extra.substr(startpos, lastpos - startpos + 1);
        }
        else {
            extra = "";
        }
        if (placeholder.at(0) == 'y' || placeholder.at(0) == 'Y'){
            cout << "In order by standard time: -ps" << endl;
            cout << "Print all at set military time: -p time" << endl;
            cout << "Add an appointment: -a Appointment Data" << endl;
            cout << "Delete all with certain title: -dt title" << endl;
            cout << "Delete all appointments with certain military time: -dm time" << endl; 
            cout << "Quit: -q" << endl;
        }
        else if (placeholder == "-ps"){
            data.at(0).standardOrder(extra, data);
        }
        else if (placeholder == "-p"){ 
            data.at(0).printMilitary(extra, data);
        }
        else if (placeholder == "-a"){
            data.at(data.size()-1).addAppointment(extra, data);
        }
        
        else if (placeholder == "-dt"){
            data.at(0).deleteTitle(extra, data);
        }
        else if (placeholder == "-dm"){
            data.at(0).deleteMilitary(extra, data);
        }

        else {
            cout << "Invalid Option" << endl;
            cout << setw(55) << setfill('-') << '-' << endl;
            cout << setfill(' ');
            cout << "See options? (yes)" << endl;
        }
        placeholder = "";
        extra = "";
        cout << "Selection: ";
        getline(cin, extra);
        cout << setfill('-') << setw(55) << '-' << endl;
        cout << setfill(' ');
    }
    return 0;
}// main
