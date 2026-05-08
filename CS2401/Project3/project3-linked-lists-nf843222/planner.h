#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

#include "date_time.h"
#include "assignment.h"
#include "node.h"


class Planner{
   public:
      Planner();
      ~Planner();
      Planner& operator =(const Planner &other);
      Planner(const Planner &other);
      void add(Assignment add);
      void display(std::ostream &cout);
      Assignment find(std::string name);
      void remove(std::string data);
      unsigned int waiting();
      unsigned int due_next();
      double average_wait();
      unsigned int oldest();
      unsigned int newest();
      void find_all(DateTime date);
      void save(std::ostream &fout);
      void load(std::istream &fin);
   private:
      node* head;
      node* tail;
};
