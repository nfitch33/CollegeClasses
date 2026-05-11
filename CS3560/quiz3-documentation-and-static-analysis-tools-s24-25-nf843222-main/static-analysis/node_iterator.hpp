#include "dnode.hpp"
#ifndef NODE_ITERATOR_H
#define NODE_ITERATOR_H

template <class T> class dlist;
template <class T> class node_iterator {
  dnode<T> *current;

public:
  friend class dlist<T>;
  node_iterator(dnode<T> *init = NULL) : current(init) {}

  // OPERATOR OVERLOADS
  bool operator!=(node_iterator other) { return current != other.current; }
  bool operator==(node_iterator other) { return current == other.current; }
  T operator*() { return current->data(); }

  node_iterator operator++() {
    current = current->next();
    return *this;
  } // prefix
  node_iterator operator++(int) {
    node_iterator orig(*this);
    current = current->next();
    return orig;
  } // postfix

  node_iterator operator--() {
    current = current->prev();
    return *this;
  } // prefix
  node_iterator operator--(int) {
    node_iterator orig(*this);
    current = current->prev();
    return orig;
  } // postfix
};

#endif
