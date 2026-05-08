/*************************************************************************
	Kyle Chiasson			Spring 2024
*************************************************************************/

#include <cstdlib>
#include <iostream>
#include <queue>
#include "queue.h"

using namespace std;

bool Chore::operator < (const Chore& other) const{
    if(priority < other.priority){
        return true;
    }
    else{
        return false;
    }
}

void Chore::input(std::istream& ins){
    getline(ins, description);
    ins >> priority;
    ins.ignore();
}

void Chore::output(std::ostream& outs) const { 
    outs << description << endl;
    outs << priority << endl;
}

void GetFiveChores(std::istream& ins, std::ostream& outs){
    //define a queue and priority queue here
    queue <Chore> num;
    priority_queue <Chore> num2;
    Chore a;
    for(int i = 0; i < 5; i++){
        a.input(ins);
        num.push(a);
        num2.push(a);
    }

    outs << "Outputting Queue:\n";
    for(int i = 0; i < 5; i++){
        // output of queue
        num.front().output(outs);
        num.pop();
    }

    outs << "Outputting Priority Queue:\n";
    for(int i = 0; i < 5; i++){
        num2.top().output(outs);
        num2.pop();
    }
}