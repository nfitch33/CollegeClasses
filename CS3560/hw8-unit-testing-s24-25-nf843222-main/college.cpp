/**
 * @file
 * @author Matthew Aberegg
 * @date October 8, 2015
 *
 * Project 3
 * CS 2401
 */
#include "college.hpp"

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

College::College(std::string s) {
  name = s;
  head = nullptr;
}

College::~College() {
  Node *rmptr;
  while (head != nullptr) {
    rmptr = head;
    head = head->link();
    delete rmptr;
  }
}

College::College(const College &other) {
  if (other.head == nullptr) {
    head = nullptr;
  } else {
    Node *sptr;
    Node *dptr;
    head = new Node(other.head->data());
    dptr = head;
    sptr = other.head->link();
    while (sptr != nullptr) {
      dptr->set_link(new Node(sptr->data()));
      dptr = dptr->link();
      sptr = sptr->link();
    }
  }
}

College &College::operator=(const College &other) {
  if (this == &other) {
    return *this;
  }
  Node *rmptr;
  while (head != nullptr) {
    rmptr = head;
    head = head->link();
    delete rmptr;
  }
  if (other.head != nullptr) {
    Node *sptr;
    Node *dptr;
    head = new Node(other.head->data());
    dptr = head;
    sptr = other.head->link();
    while (sptr != nullptr) {
      dptr->set_link(new Node(sptr->data()));
      dptr = dptr->link();
      sptr = sptr->link();
    }
  }
  return *this;
}

void College::add(Course &c) {
  Node *previous;
  Node *cursor;
  Node *newnode;
  Node *tmpptr;
  if (head == nullptr) {
    head = new Node(c);
    head->set_link(nullptr);
  } else if (head->data() > c) {
    cursor = head->link();
    head->set_link(new Node(c));
    newnode = head->link();
    newnode->set_link(cursor);
    previous = head;
    head = newnode;
    head->set_link(new Node(previous->data()));
    tmpptr = head->link();
    tmpptr->set_link(cursor);
    delete previous;
  } else if (head->data() < c) {
    cursor = head;
    while (cursor != nullptr && cursor->data() <= c) {
      previous = cursor;
      cursor = cursor->link();
    }
    if (cursor == nullptr) {
      cursor = new Node(c);
      cursor->set_link(nullptr);
      previous->set_link(cursor);
    } else {
      tmpptr = new Node(c);
      tmpptr->set_link(cursor);
      previous->set_link(tmpptr);
    }
  }
}

void College::remove(std::string coursename) {
  Node *previous;
  Node *cursor;
  if (coursename == head->data().get_course_number()) {
    cursor = head;
    head = head->link();
    delete cursor;
  } else {
    previous = head;
    cursor = head->link();
    while (cursor != nullptr &&
           cursor->data().get_course_number() != coursename) {
      previous = cursor;
      cursor = cursor->link();
    }
    if (cursor != nullptr) {
      previous->set_link(cursor->link());
      delete cursor;
    }
  }
}

void College::display(std::ostream &outs) {
  Node *ptr;
  ptr = head;
  while (ptr != nullptr) {
    outs << ptr->data().get_course_number();
    outs << ", ";
    outs << ptr->data().get_grade();
    outs << ", ";
    outs << ptr->data().get_hours();
    outs << "\n";
    ptr = ptr->link();
  }
  outs << "\n";
}

/**
 * Calculate total hours.
 *
 * @note The error in this function is intentional. No need to fix it.
 */
double College::hours() {
  Node *ptr;
  ptr = head;
  double hours = 0;
  while (ptr != nullptr) {
    hours = hours + ptr->data().get_hours();
    ptr = ptr->link();
  }
  return hours;
}

double College::gpa() {
  Node *ptr;
  ptr = head;
  double sum = 0;
  double sum_hours = 0.0;
  while (ptr != nullptr) {
    sum = sum + (ptr->data().get_number_grade() * ptr->data().get_hours());
    sum_hours += ptr->data().get_hours();
    ptr = ptr->link();
  }
  return (sum / sum_hours);
}

void College::save(std::ostream &outs) {
  Node *ptr;
  ptr = head;
  while (ptr != nullptr) {
    outs << ptr->data();
    ptr = ptr->link();
  }
}

void College::load(std::istream &ins) {
  Course tmp;
  ins >> tmp;
  Node *ptr;
  ptr = new Node;
  ptr->set_data(tmp);
  ptr->set_link(nullptr);
  head = ptr;
  while (!ins.eof()) {
    ins >> tmp;
    if (ins.eof())
      break;
    ptr->set_link(new Node);
    ptr = ptr->link();
    ptr->set_data(tmp);
    ptr->set_link(nullptr);
  }
}
