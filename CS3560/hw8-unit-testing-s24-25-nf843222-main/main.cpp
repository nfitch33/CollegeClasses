/**
 * @file
 * @author John Dolan
 * @date Spring 2015
 *
 * This is the main for Project 3, which asks you to
 * build a container that holds a list of college courses.
 * The courses are always kept in order, so they never need
 * to be sorted since they are always inserted in the order
 * where they go. You will also need the files:
 *
 * - course.hpp
 * - course.cpp
 * - node.hpp
 *
 * in order to do this project. You will be writing both the .hpp
 * and the .cpp file for the container.
 *
 * -John Dolan (Spring 2015)
 */
#include <cxxopts.hpp>
#include <fstream>
#include <iostream>
#include <string>

#include "college.hpp"
#include "course.hpp"
#include "node.hpp"

using namespace std;

// This function displays the menu and returns the user's choice
int menu();

int main(int argc, const char* argv[]) {
  int choice;
  Course c;
  string coursename;
  ifstream fin;
  ofstream fout;
  string username, filename, fullname;

  cxxopts::Options options("CollegeApp", "CLI to College class");
  options.add_options()("v,version", "Output a version of this program",
                        cxxopts::value<bool>()->default_value("false"));
  auto result = options.parse(argc, argv);

  if (result["version"].as<bool>()) {
    std::cout << "v2022.1\n";
    return EXIT_SUCCESS;
  }

  cout << "Welcome to Ohio University Course Management." << endl;
  cout << endl;
  cout << "Begin by entering your username: ";
  getline(cin, username);
  filename = username + ".txt";
  cout << "Now Enter Your Full name: ";
  while (cin.peek() == '\n') cin.ignore();
  getline(cin, fullname);
  // Here you are calling a constructor that takes a string as a
  // parameter
  College mycollege(fullname);
  fin.open(filename.c_str());
  if (!fin.fail()) {
    mycollege.load(fin);
    fin.close();
  }

  choice = menu();
  while (choice != 0) {
    switch (choice) {
      case 1:
        cout << "Enter a new course that you have taken.\n";
        cin >> c;
        mycollege.add(c);
        break;
      case 2:
        mycollege.display(cout);
        break;
      case 3:
        cout << "Enter the name/course number of the course you ";
        cout << "need to remove.\n";
        cin >> coursename;
        mycollege.remove(coursename);
        break;
      case 4:
        cout << "Total hours = " << mycollege.hours();
        break;
      case 5:
        cout << "Your current GPA = " << mycollege.gpa();
        break;
      case 6: {
        College acopy(mycollege);
        cout << "Enter one a course you would like to remove if you could.\n";
        cin >> coursename;
        acopy.remove(coursename);
        cout << "This would make your GPA: " << acopy.gpa();
        cout << "And your courselist would look like.";
        acopy.display(cout);
        cout << "But your GPA is still really: " << mycollege.gpa();
        break;
      }  // the copy goes out of scope here - destructor runs
      case 0:
        cout << "Thank you for using course management.\n";
        break;
      default:
        cout << "Not an option.\n";
        break;
    }  // bottom of the switch
    choice = menu();
  }  // bottom or the while loop, which is a senteniel loop

  fout.open(filename.c_str());
  if (!fout.fail())
    mycollege.save(fout);
  else
    cout << "Problem with saving data!\n";
  fout.close();

  return 0;
}

int menu() {
  int choice;
  cout << "\nChoose from the following options:\n";
  cout << "1) Add an additional course to your record.\n";
  cout << "2) Display all the courses taken thus far.\n";
  cout << "3) Remove a course from your college record.\n";
  cout << "4) Display the total hours thus far completed.\n";
  cout << "5) Display your current GPA.\n";
  cout << "6) Test your copy constructor.\n";
  cout << "0) Quit - saving all changes.\n";
  cin >> choice;

  return choice;
}
