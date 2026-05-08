/*************************************************************************
	This is the main for Project 3, which asks you to build a container 
	that holds a list of assignments you are waiting to complete.

    The Assignments are always kept in order, so they never need to be 
    sorted since they are always inserted in the position where they go. 

    You will also need the files:
		datetime.h
		datetime.cc
		assignment.h
		assignment.cc
		node.h
    in order to do this project. You will be writing both the .h
    and the .cc file for the container.

	Patricia Lindner	February 2024
*************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "assignment.h"
#include "node.h"
#include "planner.h"

using namespace std;

// This function displays the menu and returns the user's choice
char menu();

int main(){
    char choice, ch;
    Assignment a, found;
    DateTime due_by;
    string assignmentname;
    ifstream fin;
    ofstream fout;
    string username, filename, fullname;

	cout << "Welcome to your Homework Assignment Manager.\n\n";
	cout << "Begin by entering your username: ";
	getline(cin, username);
	filename = username + ".txt";
	// The default constructor is called here
	Planner homework;
    fin.open(filename.c_str());
    if(!fin.fail()){
        homework.load(fin);
        fin.close();
	}
	choice = menu();
	while(choice != '0'){
	    switch(choice){
			case '1':
				cout << "Enter the assignment information.\n";
				cin >> a;
				homework.add(a);
				break;
			case '2':
				homework.display(cout);
                cout << endl;
				break;
			case '3':
				cout << "Enter the name of the assignment that you have completed.\n ";
				cin >> ws;
				getline(cin, assignmentname);
                found = homework.find(assignmentname);
                if(found != Assignment()){
                    cout << found << endl;
                    cout << "Do you want to remove this assignment? (y/n)\n";
                    cin >> ch;
                    if(tolower(ch) == 'y'){
                        homework.remove(assignmentname);
                    }
                }
				break;
			case '4':
				cout << "\nNumber of assignments waiting to be completed = " << homework.waiting() << endl << endl;
				break;
			case '5':{
				unsigned due = homework.due_next();
				if(due == 0){
					cout << "\nThe next assignment you need to complete is past due.\n\n";
				}
				else{
					cout << "\nThe assignment due next is due in ";
					convert_minutes(due);
					cout << endl << endl;
				}
				break;
			}
			case '6':
				cout << "\nThe average wait time of all assignments is : ";
				convert_minutes(homework.average_wait());
				cout << endl << endl;;
				break;
			case '7':
				cout << "\nThe assignment entered longest ago was entered ";
                convert_minutes(homework.oldest());
                cout << " ago\n\n";
				break;
			case '8':
				cout << "\nThe assignment entered most recently was entered ";
                convert_minutes(homework.newest());
                cout << " ago\n\n";
				break;
			case '9':
                cout << "\nEnter a date: ";
				cin >> ws;
				due_by.input(cin);
                cout << "\nAssignments due by then:\n";
                homework.find_all(due_by);
               	break;
			case '0':
				cout << "Thank you for using the Assignment Manager.\n";
				break;
			case 't':{   // copy constructor test
				Planner acopy(homework); // you must write all 3 of the Big 3
				cout << "Enter the name of the assignment that is to be removed.\n ";
				cin >> ws;
				getline(cin, assignmentname);
				acopy.remove(assignmentname);
				acopy.display(cout);
				cout << "Number waiting = " << acopy.waiting() << endl;
				break;
			}  // copy goes out of scope
			default:
				cout << "Not an option.\n";
				break;
			} //bottom of the switch
	    choice = menu();
	}// bottom or the while loop, which is a senteniel loop

    fout.open(filename.c_str());
    if(!fout.fail())
		homework.save(fout);
    else
		cout << "Problem with saving data!\n";
    fout.close();

	return 0;
}

char menu(){
    char choice;

    cout << "Choose from the following options:\n";
    cout << "1) Add an assignment to the list.\n";
    cout << "2) Display all the assignments in the list.\n";
    cout << "3) Remove an assignment you have completed.\n";
    cout << "4) Display number of assignments waiting to be completed.\n";
    cout << "5) Display how long you have to complete the next assignment due.\n";
    cout << "6) Average wait time for all assignments currently in the list.\n";
    cout << "7) Display how long the oldest assignment has been waiting. \n";
    cout << "8) Display how long the newest assignment has been waiting. \n";
    cout << "9) Show all assignments due before a specified date. \n";
    cout << "0) Quit - saving all changes.\n";
    cin >> choice;

    return choice;
}