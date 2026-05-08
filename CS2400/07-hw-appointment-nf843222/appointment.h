
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <fstream>
using namespace std;

class Appointment {
    public :
    Appointment(); // Works
    Appointment(string appData); // Works
    string getTitle(); // Works
    int getYear(); // Works
    int getMonth(); // Works
    int getDay(); // Works
    int getTime(); // Works
    string getDate(); // Works
    int getDuration(); // Works
    string getStandardTime(); // Works // Might need to change
    void setTitle(string newTitle); // Works
    void setYear(int newYear); // Works
    void setMonth(int newMonth); // Works
    void setDay(int newDay); // Works
    void setTime(int newTime); // Works
    void setDate(int newYear, int newMonth, int newDay); // Works
    void setDuration(int newDuration); // Works
    int standardToMilitary(string time); // Works
    string militaryToStandard(int time); // Works

    private :
    string title;
    int year;
    int month; 
    int day;
    int time;
    int duration;
};