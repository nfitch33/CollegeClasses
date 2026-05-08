#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

#ifndef DNODE_H
#define DNODE_H

using namespace std;

template<class t>
class dnode{
    public:
        dnode(t i = NULL, dnode* n = nullptr, dnode* p = nullptr);
        t data(){return item;}
        void set_item(t value){item = value;}
        void set_next(dnode* n){nex = n;}
        dnode* next(){return nex;}
        void set_previous(dnode* p){previou = p;}
        dnode* previous(){return previou;}

    private:
        t item;
        dnode* nex;
        dnode* previou;

};
template<class t>
dnode<t>::dnode(t i, dnode* n, dnode* p){
    item = i;
    nex = n;
    previou = p;
}

#endif