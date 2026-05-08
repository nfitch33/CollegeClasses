/*************************************************************************
	Kyle Chiasson			Spring 2024
*************************************************************************/

#ifndef QUEUE_H
#define QUEUE_H

#include <cstdlib>
#include <iostream>
#include <queue>

class Chore{
    public:
        bool operator <(const Chore& other) const;
        void input(std::istream& ins);
        void output(std::ostream& outs) const;
    private:
        std::string description = "";
        int priority = 0;
};

void GetFiveChores(std::istream& ins, std::ostream& outs);

#endif