
#ifndef DLIST_H
#define DLIST_H
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include "dnode.h"
#include "node_iterator.h"

using namespace std;

template<class t>
class dlist{
    public:
        dlist(){head = tail = nullptr;}
        ~dlist();
        dlist& operator =(const dlist &other);
        dlist(const dlist &other);
        size_t size();
        void show();
        void reverse_show();
        void front_insert(t i);
        void rear_insert(t i);
        void front_remove();
        void rear_remove();
        typedef node_iterator<t> iterator;
        iterator r_begin() const; // (return an iterator pointing to the end of the list)  
        iterator r_end() const; // (return an iterator pointing to nullptr - the "past the end" element)  
        iterator begin() const; // (return an iterator pointing to the beginning of the list)  
        iterator end() const; // (return an iterator pointing to nullptr - the "past the end" element)  
        void insert_before(iterator temp, t i);
        void insert_after(iterator temp, t i);
        void remove(iterator temp);

    private:
        dnode<t>* head;
        dnode<t>* tail;
};

#include "dlist.template"
#endif