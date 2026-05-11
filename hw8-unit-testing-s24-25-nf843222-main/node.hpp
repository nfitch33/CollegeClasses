/**
 * @file
 * @author Main/Savitch, John Dolan
 * @date March 2009
 *
 * This file is borrowed heavily from Main/Savitch "Data Structures and
 * Other Object Using C++," Chapter 5. It features a node class that
 * can be used in the construction of linked lists.
 * -John Dolan (March 2009)
 */
#pragma once
#include "course.hpp"

/**
 * Node representation of a linked list.
 */
class Node {
public:
  typedef Course value_type;
  // Universal constructor
  Node(value_type d = value_type(), Node* l = nullptr) {
    data_field = d;
    link_field = l;
  }

  // Mutator functions
  void set_data(value_type d) { data_field = d; }
  void set_link(Node* l) { link_field = l; }

  // Accessor functions
  value_type data() const { return data_field; }
  Node* link() { return link_field; }
  const Node* link() const { return link_field; }

private:
  value_type data_field;
  Node* link_field;
};
