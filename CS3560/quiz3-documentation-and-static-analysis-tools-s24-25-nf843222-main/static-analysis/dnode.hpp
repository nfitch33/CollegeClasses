#ifndef DNODE_H
#define DNODE_H
#include <iostream>

template <class T> class dnode {
  T datafield;
  dnode *next_link;
  dnode *prev_link;

public:
  dnode(T &dat = T(), dnode *nlink = NULL, dnode *plink = NULL)
      : datafield(dat), next_link(nlink), prev_link(plink) {}

  dnode *prev() { return prev_link; }
  dnode *next() { return next_link; }
  T data() { return datafield; }

  const dnode *prev() const { return prev_link; }
  const dnode *next() const { return next_link; }
  const T data() const { return datafield; }

  void set_next(dnode *n) { next_link = n; }
  void set_prev(dnode *p) { prev_link = p; }
  void set_data(T &d) { datafield = d; }
};
#endif
