
#ifndef NODE_ITERATOR_H
#define NODE_ITERATOR_H

#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include "dnode.h"
#include "dlist.h"


using namespace std;

template<class T>
class dlist;

template<class T>
class node_iterator{
    public:
    node_iterator(dnode<T>* c = nullptr){cursor = c;}
    node_iterator operator++();
    node_iterator operator++(int);
    node_iterator operator--();
    node_iterator operator--(int);
    bool operator==(const node_iterator& other) const;
    bool operator!=(const node_iterator& other) const;
    T operator *() const;

    private:
    dnode<T>* cursor;
    friend class dlist<T>;
};

#include "node_iterator.template"
#endif