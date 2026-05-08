/*************************************************************************
 * This class is a container that holds objects of the class Profile.
 * It uses an internal iterator to give the application the ability to
 * order the container and access the elements in the container.
 * Because it uses dynamic memory, it must have the Big 3.
 * 
 * Patricia Lindner     Spring 2024		Ohio University EECS
*************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include "profile.h"
#ifndef INSTAF_H
#define INSTAF_H

class InstaFollows{
    public:
        InstaFollows();

        //The functions known as the Big 3
        ~InstaFollows(); // Deconstructor
        InstaFollows(const InstaFollows& other); // Copier
        void operator = (const InstaFollows& other); // ??

        // Functions for the internal iterator
        void start(); // Sets current_index to 0
        void advance(); // Increments current_index by 1
        bool is_item()const; // Makes sure current_index is not greater than used
        Profile current()const;
        void remove_current(); // Removes where current_index is located and moves the data back
        void insert(const Profile& p); // Puts data to the right of current index.
        void attach(const Profile& p); // Puts data to the left of current index.
        
        // Other useful functions
        void show_all(std::ostream& outs)const; // Shows all profiles
        void bday_sort(); // Sorts profiles by birthday
        Profile find_profile(const std::string& name)const; // Finds a profile using a name
        bool is_profile(const Profile& p) const; // Sees if profile is in data set

        // File I/O functions
        void load(std::istream& ins);   // Loads from file to data
        void save(std::ostream& outs)const; // Loads data to file

    private:
        Profile *data;
        size_t used;
        size_t capacity;
        size_t current_index;

        void resize();
};

#endif