#ifndef DLIST_H
#define DLIST_H
#include "dnode.hpp"
#include "node_iterator.hpp"

template <class T> class dlist {
  dnode<T> *head;
  dnode<T> *tail;

public:
  typedef node_iterator<T> iterator;

  dlist() { head = tail = NULL; }
  dlist(const dlist &other);
  dlist &operator=(const dlist &other);
  ~dlist();

  iterator begin() { return iterator(head); }
  iterator end() {
    return iterator();
  } // returns iterator set to NULL (DOES NOT RETURN NULL)
  iterator r_begin() {
    return iterator(tail);
  } // reverse begin (the end of the list)
  iterator r_end() { return iterator(); }
  void insert_before(iterator it, T item);
  void insert_after(iterator it, T item);
  int size();
  void remove(iterator it);

  void destroy();
  void copy(const dlist &other);
  void front_insert(T &dat);
  void rear_insert(T &dat);
  void front_remove();
  void rear_remove();
  void show();
  void reverse_show();
};

#include "dlist.template"

#endif
