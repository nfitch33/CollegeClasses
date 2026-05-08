#include <iostream>
#include "profile.h"
#include "instafollows.h"
using namespace std;

Profile::Profile(std::string n, Date d){
    name = n;
    bday = d;
}

std::string Profile::get_name()const{
    return name;
}

Date Profile::get_bday()const{
    return bday;
}

bool Profile::operator == (const Profile& other)const{ // CORRECT
    if (bday == other.bday){
        if (name == other.name){
            return true;
        }
    }
    return false;
}

bool Profile::operator != (const Profile& other)const{ // CORRECT
    if (bday != other.bday){
        return true;
    }
    else if(name != other.name){
        return true;
    }
    else{
        return false;
    }
}

void Profile::input(std::istream& ins){
    getline(ins, name);
    ins >> bday;
    ins.ignore();
}

void Profile::output(std::ostream& outs)const{
    outs << name << endl;
    outs << bday << endl;
}

// OUTSIDE CONSTRUCTOR
std::istream& operator >> (std::istream& ins, Profile& p){
    p.input(ins);
    return ins;
}

std::ostream& operator << (std::ostream& outs, const Profile& p){
    p.output(outs);
    return outs;
}