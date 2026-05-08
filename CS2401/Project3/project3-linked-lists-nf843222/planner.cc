#include<iostream>
#include<fstream>
#include<cctype>
#include <cstdlib>
#include<string>

#include "planner.h"
#include "date_time.h"
#include "assignment.h"
#include "node.h"

using namespace std;

Planner::Planner(){
    head = nullptr;
    tail = nullptr;
}
Planner::~Planner(){
    node* cursor = head;
    while(cursor != nullptr){
        head = cursor;
        cursor = cursor->next();
        delete head;
    }
}
Planner::Planner(const Planner& other){
    node* cursor = other.head;
    if(cursor == nullptr){
        head = nullptr;
        tail = nullptr;
        return;
    }

    head = new node(other.head -> data());
    cursor = cursor -> next();
    tail = head;
	while(cursor != nullptr){
		tail -> set_next(new node(cursor -> data()));
		tail = tail->next();
		cursor = cursor->next();
	}

}
Planner& Planner::operator =(const Planner& other){
    if(this == &other){
        return *this;
    }
    node* cursor = other.head;
    if(cursor == nullptr){
        head = nullptr;
        tail = nullptr;
        return *this;
    }

    head = new node(other.head -> data());
    cursor = cursor -> next();
    tail = head;
	while(cursor != nullptr){
		tail -> set_next(new node(cursor -> data()));
		tail = tail->next();
		cursor = cursor->next();
	}
    return *this;
}

void Planner::add(Assignment add){
    //FUNCTION FOR INSERTING ASSIGNMENTS
node* cursor = head;
node* stopper = head;
int last = 0;
//empty
if(head == nullptr){
    head = new node(add);
    head -> set_next(nullptr);
    return;
}
while(add.get_due() > cursor->data().get_due()){
    if(cursor -> next() == nullptr){
        last++;
        break;
    }
    cursor = cursor->next();
}

//needs to go first
if(cursor == head && last == 0){
    head = new node(add);
    head -> set_next(cursor);
}
//needs to go last
else if(last == 1 && add.get_due() > cursor->data().get_due()) {
    cursor -> set_next(new node(add));
    cursor = cursor->next();
    cursor->set_next(nullptr);
}
//needs to go in middle
else{
    stopper = cursor;
    cursor = head;
    while(cursor -> next() != stopper){
        cursor = cursor->next();
    }
    cursor -> set_next(new node(add));
    cursor = cursor->next();
    cursor->set_next(stopper);
}

}
void Planner::display(std::ostream &cout){
    node* cursor = head;
    while(cursor != nullptr){
        cout << cursor->data();
        cursor = cursor->next();
    }
}
Assignment Planner::find(std::string name){
    node* cursor = head;
    while(cursor != nullptr){
        if(cursor -> data().get_name() == name){
            return cursor->data();
        }
        cursor = cursor->next();
    }
    Assignment a;
    return a;
    
}
void Planner::remove(std::string name){
    node* cursor = head;
    node* stopper = head;
    if(head == nullptr){
        return;
    }
    while(cursor -> data().get_name() != name){
        cursor = cursor->next();
        if(cursor == nullptr){
            return;
        }
    }
    if(cursor -> data().get_name() == name && cursor == head){
        stopper = stopper->next();
        delete cursor;
        head = stopper;
    }
    else if(cursor->data().get_name() == name && cursor -> next() == nullptr){
        while(stopper -> next() != cursor){
            stopper = stopper->next();
        }
        stopper->set_next(nullptr);
        delete cursor;
    }
    else{
        while(stopper->next() != cursor){
            stopper = stopper->next();
        }
        stopper->set_next(cursor->next());
        delete cursor;
    }
}
unsigned int Planner::waiting(){
    node* cursor = head;
    int nodecount = 0;
    while(cursor != nullptr){
        nodecount++;
        cursor = cursor->next();
    }
    return nodecount;
}
unsigned int Planner::due_next(){
    if(head == nullptr){
        return 0;
    }
    return head->data().minutes_til_due();
}
double Planner::average_wait(){
    node* cursor = head;
    double minutes = 0;
    int total = 0;
    if(head == nullptr){
        return 0;
    }
    while(cursor != nullptr){
        minutes += cursor->data().minutes_waiting();
        cursor = cursor->next();
        total++;
    }
    minutes = minutes / total;
    return minutes;
}
unsigned int Planner::oldest(){
    node* cursor = head;
    node* stopper = head;
    if(head == nullptr){
        return 0;
    }
    while(cursor != nullptr){
        if(cursor -> data().minutes_waiting() > stopper -> data().minutes_waiting()){
            stopper = cursor;
        }
        cursor = cursor->next();
    }
    return stopper->data().minutes_waiting();
}
unsigned int Planner::newest(){
    node* cursor = head;
    node* stopper = head;
    if(head == nullptr){
        return 0;
    }
    while(cursor != nullptr){
        if(cursor -> data().minutes_waiting() < stopper -> data().minutes_waiting()){
            stopper = cursor;
        }
        cursor = cursor->next();
    }
    return stopper->data().minutes_waiting();
}
void Planner::find_all(DateTime date){
    node* cursor = head;
    while(cursor != nullptr){
        if(cursor -> data().get_due() < date){
            cout << cursor -> data();
        }
        cursor = cursor -> next();
    }
}
void Planner::save(std::ostream &fout){
    node* cursor = head;
    if(cursor == nullptr){
        return;
    }
    while(cursor != nullptr){
        fout << cursor->data();
        cursor = cursor->next();
    }
}

void Planner::load(std::istream &fin){
    Assignment Hello;
    fin >> Hello;
    while(!fin.fail()){
        add(Hello);
        fin >> Hello;
    }
}
