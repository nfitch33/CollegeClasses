/**
 * @file
 * @author Matthew Aberegg
 * @date October 8, 2015
 *
 * Project 3
 * CS 2401
 */
#pragma once
#include <fstream>
#include <iostream>
#include <string>

#include "course.hpp"
#include "node.hpp"

/**
 * A representation of a college.
 *
 * Basically the linked list of Course(s).
 **/
class College {
public:
  College(std::string s);
  ~College();
  College(const College& other);
  College& operator=(const College& other);
  void add(Course& c);
  void remove(std::string coursename);
  void display(std::ostream& outs);
  double hours();
  double gpa();
  void save(std::ostream& outs);
  void load(std::istream& ins);

  // accessor functions
  std::string get_college_name() const { return name; }

private:
  std::string name;
  Node* head;
};
