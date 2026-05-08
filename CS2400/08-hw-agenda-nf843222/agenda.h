
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <fstream>
using namespace std;

class Appointment {
    public :
    Appointment(); // SETS DEFAULT VALUES
    Appointment(string appData); // SETS VALUES
    string getTitle(); // grabs the title
    int getYear(); // grabs the year
    int getMonth(); // grabs the month
    int getDay(); // grabs the day
    int getTime(); // grabs military time
    string getDate(); // grabs the date as a whole
    int getDuration(); // grabs duration
    string getStandardTime(); // converts military to standard and grabs it
    void setTitle(string newTitle); // sets a new title
    void setYear(int newYear); // sets a new year
    void setMonth(int newMonth); // sets a new month
    void setDay(int newDay); // sets a new day
    void setTime(int newTime); // sets a new time
    void setDate(int newYear, int newMonth, int newDay); // sets a new date
    void setDuration(int newDuration); // sets a new duration
    int standardToMilitary(string time); // converts standard to military
    string militaryToStandard(int time); // converts military to standard
    void printMilitary(string extra, vector<Appointment> data); // prints all info with military time
    void addAppointment(string extra, vector<Appointment> &data); // adds an appointment
    void deleteTitle(string extra, vector<Appointment> &data);  // deletes all appointments with same title
    void deleteMilitary(string extra, vector<Appointment> &data); // deletes all appointments with the same military time
    void standardOrder(string extra, vector<Appointment> &data);  // puts all the information in order from standard time
    // bool operator < (vector<Appointment> &data);

    private :
    string title;
    int year;
    int month;  // ALL PRIVATE INFO
    int day;
    int time;
    int duration;
};
void toupper(string &UPPER); // HELPER FUNCTION