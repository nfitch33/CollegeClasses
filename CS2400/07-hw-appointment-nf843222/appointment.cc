
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <fstream>
#include "appointment.h"
using namespace std;

Appointment::Appointment(){ // Default constructor
    title = "N/A";
    year = 1;
    month = 1;
    day = 1;
    time = 0;
    duration = 1;
}
Appointment::Appointment(string appData){ // Uses a switch to help with the ordering of the appointment
    int bar = 0;
    string temp;
    int space;
    string placeholder = "";
    for (size_t x = 0; x < appData.length(); x++){
        if (appData.at(x) == '|'){
            bar++;
            x++;
            switch(bar){
                case 1: // Title case
                    space = placeholder.find(" ");
                    placeholder.erase(placeholder.begin() + space);
                    setTitle(placeholder);
                    placeholder = "";
                    break;
                case 2: // Year case
                    setYear(stoi(placeholder));
                    placeholder = "";
                    break;
                case 3: // Month Case
                    setMonth(stoi(placeholder));
                    placeholder = "";
                    break;
                case 4: // Day case
                    setDay(stoi(placeholder));
                    placeholder = "";
                    break;
                case 5: // Time case
                    for (size_t x = 0; x < placeholder.length(); x++){
                        if (placeholder.at(x) == ' '){
                            placeholder.erase(placeholder.begin() + x);
                        }
                    }
                    setTime(standardToMilitary(placeholder));
                    placeholder = "";
                    break;

                default:
                break;
            }
        }
        placeholder = placeholder + appData.at(x);
    } // Duration Case
    setDuration(stoi(placeholder));
}
string Appointment::getTitle(){ // Outputs current title
    return title;
}
int Appointment::getYear(){ // Outputs current Year
    return year;
}
int Appointment::getMonth(){ // Outputs current Month
    return month;
}
int Appointment::getDay(){ // Outputs current Day
    return day;
}
int Appointment::getTime(){ // Outputs current Time
    return time;
}
string Appointment::getDate(){ // Outputs current Date
    string date;
    string daily;
    string monthly;
    date = to_string(year);
    date = date + '-';
    monthly = to_string(month);
    daily = to_string(day);
    if (month < 10){
        monthly = '0' + monthly;
    }
    date = date + monthly;
    date = date + '-';
    if (day < 10){
        daily = '0' + daily;
    }
    date = date + daily;
    return date;
}
int Appointment::getDuration(){ // Outputs current duration
    return duration;
}
string Appointment::getStandardTime(){ // outputs standard Time
    string standard = militaryToStandard(time);
    return standard;
}
string Appointment::militaryToStandard(int time){ // Turns Military to Standard Time
    string timeSet;
    string placeholder;
    string standard;
    int newTime;
    if (time < 1200){
        placeholder = to_string(time);
        timeSet = "AM";
        if (placeholder.length() == 3){
            standard = placeholder.substr(0,1) + ":" + placeholder.substr(1, placeholder.length() - 1) + timeSet;
        }
        else if (placeholder.length() == 4){
            standard = placeholder.substr(0,2) + ":" + placeholder.substr(2,placeholder.length() - 1) + timeSet;
        }
        else if (placeholder.length() == 1){
            standard = "12:0" + placeholder + "AM";
        }
        else if (placeholder.length() == 2){
            standard = "12:" + placeholder + "AM";
        }
    }
    else if (time >= 1200) {
        timeSet = "PM";
        newTime = time - 1200;
        placeholder = to_string(newTime);
        if (placeholder.length() == 3){
            standard = placeholder.substr(0,1) + ":" + placeholder.substr(1, placeholder.length() - 1) + timeSet;
        }
        else if (placeholder.length() == 4){
            standard = placeholder.substr(0,2) + ":" + placeholder.substr(2,placeholder.length() - 1) + timeSet;
        }
        else if (placeholder.length() == 1){
            standard = "12:0" + placeholder + "PM";
        }
        else if (placeholder.length() == 2){
            standard = "12:" + placeholder + "PM";
        }
    }
    return standard;
}
int Appointment::standardToMilitary(string standardTime){ // Puts standard into military time
    int placeholder;
    int x;
    string placeholder2;

    x = standardTime.find(":");
    standardTime.erase(standardTime.begin() + x);
    
    string timeSet = standardTime.substr(standardTime.length() - 2);
    standardTime = standardTime.substr(0, standardTime.length() - 2);
    if (standardTime.at(standardTime.length() - 1) == ' '){
        standardTime.erase(standardTime.begin() + standardTime.length() - 1);
    }
    placeholder = stoi(standardTime);
    if (timeSet.at(0) == 'p'){
        timeSet.at(0) = 'P';
    }
    else if (timeSet.at(0) == 'a'){
        timeSet.at(0) = 'A';
    }
    timeSet.at(1) = 'M';
    if (timeSet == "PM" && placeholder == 1200){
        time = 1200;
        return time;
    }
    else if (timeSet == "PM" && placeholder > 1200){
        time = placeholder + 1200;
        return time;
    }
    else if (timeSet == "PM" && placeholder < 1200){
        placeholder = placeholder + 1200;
        time = placeholder;
        return time;
    }
    else if (timeSet == "AM" && placeholder > 1200){
        time = placeholder - 1200;
        return time;
    }
    else if (timeSet == "AM" && placeholder == 1200){
        time = 0;
        return time;
    }
    else if (timeSet == "AM" && placeholder < 1200){
        time = placeholder;
        return time;
    }
}
void Appointment::setTitle(string newTitle){ // Sets new title if accessible
    if (newTitle.at(0) == ' '){
        newTitle.erase(newTitle.begin());
    }
    if (newTitle.at(0) == ' '){
        newTitle.erase(newTitle.begin());
    }
    if (newTitle.at(newTitle.length() - 1) == ' '){
        newTitle.erase(newTitle.begin() + newTitle.length() - 1);
    }
    if (newTitle.at(newTitle.length() - 1) == ' '){
        newTitle.erase(newTitle.begin() + newTitle.length() - 1);
    }
        title = newTitle;
}

void Appointment::setYear(int newYear){ // Sets new year if accessible
    if (newYear > 0){
        year = newYear;
    }
}
void Appointment::setMonth(int newMonth){ // Sets new Month if accessible
    if(newMonth <= 12 && newMonth >= 1){
        month = newMonth;
    }
}
void Appointment::setDay(int newDay){ // Sets new Day if accessible
    if (year % 4 == 0 && month == 2){
        if (newDay < 30 && newDay >= 1){
            day = newDay;
        }
    }
    else if (year % 4 != 0 && month == 2){
        if (newDay < 29 && newDay >= 1){
            day = newDay;
        }
    }
    else if (month % 2 == 1 && month < 8){
        if (newDay <= 31 && newDay >= 1){
            day = newDay;
        }
    }
    else if (month % 2 == 1 && month > 7){
        if (newDay <= 30 && newDay >= 1){
            day = newDay;
        }
    }
    else if (month % 2 == 0 && month > 7){
        if (newDay >= 1 && newDay <= 31){
            day = newDay;
        }
    }
    else {
        if (newDay >= 1 && newDay <= 30){
            day = newDay;
        }
    }
}

void Appointment::setTime(int newTime){ // Sets new time if accessible
    string placeholder;
    if (newTime <= 2359 && newTime >= 0){
        placeholder = to_string(newTime);
        if (placeholder.length() == 4){
            if (placeholder.at(2) <= '5' && placeholder.at(2) >= '1'){
                    time = newTime;
            }
        }
        else if (placeholder.length() == 3){
            if (placeholder.at(1) <= '5' && placeholder.at(1) >= '1'){
                time = newTime;
            }
        }
}
}
void Appointment::setDate(int newYear, int newMonth, int newDay){ // sets new date if accessible
    setYear(newYear);
    setMonth(newMonth);
    setDay(newDay);
}
void Appointment::setDuration(int newDuration){ // Sets new duration if accessible
    if (newDuration > 0){
        duration = newDuration;
    }
}
