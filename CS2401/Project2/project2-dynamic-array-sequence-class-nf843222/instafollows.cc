#include <iostream>
#include <fstream>
#include <string>
#include "instafollows.h"
#include "profile.h"

using namespace std;
InstaFollows::InstaFollows(){
    used = 0;
    capacity = 5;
    current_index = 0;
    data = new Profile[capacity];
}

//         //The functions known as the Big 3
InstaFollows::~InstaFollows(){
    delete []data;
}

InstaFollows::InstaFollows(const InstaFollows& other){ // COPY FUNCTION
    capacity = other.capacity;
    used = other.used;
    current_index = other.current_index;
    data = new Profile[capacity];
    for(size_t x = 0; x < used; x++){
        data[x] = other.data[x];
    }
}

void InstaFollows::operator = (const InstaFollows& other){
    if (this == &other){
        return;
    }
    else {
        delete []data;
        capacity = other.capacity;
        used = other.used;
        current_index = other.current_index;
        data = new Profile[capacity];
        for(size_t x = 0; x < used; x++){
            data[x] = other.data[x];
        }
    }
}

        // Functions for the internal iterator
void InstaFollows::InstaFollows::start(){
    current_index = 0;
}

void InstaFollows::InstaFollows::advance(){
    current_index++;
}

bool InstaFollows::InstaFollows::is_item()const{
    if(current_index >= used){
        return false;
    }
    return true;
}

Profile InstaFollows::current()const{
    if(current_index >= used){
        Profile p;
        return p;
    }
    return data[current_index];
}

void InstaFollows::remove_current(){
    if(current_index >= used){
        return;
    }
    for(size_t x = current_index; x < used - 1; x++){
        data[x] = data[x+1];
    }
    used--;
}

void InstaFollows::insert(const Profile& p){
    if (used == capacity){
        resize();
    }
    if(is_item()){
        for(size_t x = used; x > current_index; x--){
            data[x] = data[x - 1];
        }
        data[current_index] = p;
    }
    else{
        for(size_t x = used; x > 0; x--){
            data[x] = data[x - 1];
        }
        data[0] = p;
    }
    current_index++;
    used++;
}

void InstaFollows::attach(const Profile& p){
    if(used == capacity){
        resize();
    }
    if(is_item()){
        for(size_t x = used; x > current_index + 1; x--){
            data[x] = data[x - 1];
        }
        data[current_index + 1] = p;
    }
    else{
        data[used] = p;
    }
    used++;
}
        
        // Other useful functions
void InstaFollows::show_all(std::ostream& outs)const{
    for (size_t x = 0; x < used; x++){
        outs << data[x];
    }
}

void InstaFollows::bday_sort(){
    Profile extra;
    for(size_t i = 0; i < used - 1; ++i){
		for (size_t j = 0; j < used - i - 1; ++j){
			if (data[j].get_bday() > data[j+1].get_bday()){
				extra = data[j];
				data[j] = data[j+1];
				data[j+1] = extra;
			}
		}
	}
}


Profile InstaFollows::find_profile(const std::string& name)const{ // NOT FINISHED
    for (size_t x = 0; x < used; x++){
        if (data[x].get_name() == name){
            return data[x];
        }
    }
    Profile extra;
    return extra;
}

bool InstaFollows::is_profile(const Profile& p) const{
    for (size_t x = 0; x < used; x++){
        if (data[x] == p){
            return true;
        }
    }
    return false;
}

        // File I/O functions
void InstaFollows::load(std::istream& ins){
    Profile test;
    ins >> test;
    while(!ins.eof()){
        if (used == capacity){
            resize();
        }
        data[used] = test;
        ins >> test;
        used++;
    }
}

void InstaFollows::save(std::ostream& outs)const{ 
    for (size_t x = 0; x < used; x++){
        outs << data[x];
    }
}

// PRIVATE
void InstaFollows::resize(){
        Profile *extra = new Profile[capacity + 5];
        for(size_t x = 0; x < used; x++){
            extra[x] = data[x];
        }
        delete []data;
        capacity += 5;
        data = new Profile[capacity];
        for(size_t x = 0; x < used; x++){
            data[x] = extra[x];
        }
}