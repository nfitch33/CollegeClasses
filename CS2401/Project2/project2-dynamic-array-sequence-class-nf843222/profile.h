/*************************************************************************
 * This is the header file for a class called Profile. It holds some Profile
 * information about a single Instagram profile, just their name and 
 * birthday. It uses a class called Date for the storage of the birthday. 
 * The member functions are just accessors and input/output functions.
 * 
 * Patricia Lindner	    Spring 2024		Ohio University
*************************************************************************/

#include <iostream>
#include <string>
#include "date.h"
#ifndef PROFILE_H
#define PROFILE_H

class Profile{
    public:
		Profile(std::string n = "N/A", Date d = Date()); 
		std::string get_name()const; // returns name
		Date get_bday()const;	// returns day
		bool operator == (const Profile& other)const; // checks if two profiles are equal to each other... overloads == function
		bool operator != (const Profile& other)const; // checks if two profiles are not equal to each other... overloads != function
		void input(std::istream& ins);	// inputs name and birthday to data
		void output(std::ostream& outs)const; // outputs name and birthday to file
		
    private:
		std::string name;
		Date bday;
};

std::istream& operator >> (std::istream& ins, Profile& p); // overloads >> function
std::ostream& operator << (std::ostream& outs, const Profile& p); // overloads << function

#endif