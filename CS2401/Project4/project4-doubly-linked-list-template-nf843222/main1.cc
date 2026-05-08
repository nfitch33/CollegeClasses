/*************************************************************************
   This main is to be used as a testing platform as you develop your
   dlist class and the associated dnode and dnode iterator classes for 
   project 4.
   
   After you have developed each function you should uncomment the code 
   that calls that function, recompile everything and run the test. If it
   crashes, fix that function before moving on.

   John Dolan				Spring 2014
   Patricia Lindner     March 2024
*************************************************************************/
#include <iostream>
#include "dlist.h"

using namespace std;

int main(){
   // default constructor for the list
   dlist<int> lis1, lis2;

   // testing rear_insert and show
/*
   cout << "Rear insert:\n";
   int tmp;
   for(int i = 0; i < 10; ++i)
	   lis1.rear_insert(i);
   lis1.show();
   cout << endl << endl;
*/

// testing front_insert and show
/*
   cout << "Front insert:\n";
   for(int i = 100; i < 110; ++i)
	   lis2.front_insert(i);    
   lis2.show();
   cout << endl << endl;
*/

// testing the front and rear removes
/*
   cout << "Front and rear remove:\n";
   lis1.front_remove();
   lis1.rear_remove();
   lis1.show();
   cout << endl << endl;
*/

// testing if the list can be traversed in both directions
/*
   cout << "Reverse show:\n";
   lis1.reverse_show();
   cout << endl << endl;
*/

// declaring an iterator and using it to traverse list frontwards
/*
   cout << "Traverse front-to-back with iterator:\n";
   dlist<int>::iterator it1;
   for(it1 = lis1.begin(); it1 != lis1.end(); ++it1)
	   cout << *it1 << endl;
   cout << endl << endl;
*/

// using iterator to traverse list backwards
/*
   cout << "Traverse back-to-front with iterator:\n";
   for(it1 = lis1.r_begin(); it1 != lis1.r_end(); --it1)
	   cout << *it1 << endl;
   cout << endl << endl;
*/

// moving the iterator to the fourth element and putting 89 before that
/*
   cout << "Insert before iterator:\n";
   it1 = lis1.begin();
   for(int i = 0; i < 3; ++it1, ++i)
	   ;

   tmp = 89;
   lis1.insert_before(it1, tmp);

   cout << "List 1 front-to-back after insert_before:\n";
   for(it1 = lis1.begin(); it1 != lis1.end(); ++it1)
      cout << *it1 << endl;
   cout << endl << endl;

   cout << "List 1 back-to-front after insert_before:\n";
   for(it1 = lis1.r_begin(); it1 != lis1.r_end(); --it1)
        cout << *it1 << endl;
   cout << endl << endl;
*/

// traversing the second list from the rear and putting 256 in middle
/*
   cout << "Insert after iterator:\n";
   tmp = 256;
   it1 = lis2.r_begin();
   for(int i = 0; i < lis2.size() / 2; --it1, ++i)
      ;
   lis2.insert_after(it1, tmp);

   cout << "List 2 front-to-back after insert_after:\n";
   for(it1 = lis2.begin(); it1 != lis2.end(); ++it1)
      cout << *it1 << endl;
   cout << endl << endl;

   cout << "List 2 back-to-front after insert_after:\n";
   for(it1 = lis2.r_begin(); it1 != lis2.r_end(); --it1)
      cout << *it1 << endl;
   cout << endl << endl;
*/

// testing copy constructor and assignment operator
/*
{
   cout << "Copy constructor and assignment operator:\n";
   dlist<int> copy(lis1);
   lis1 = lis2;

   cout << "List 1 front-to-back (should be original list 2 numbers):\n";
   for(it1 = lis1.begin(); it1 != lis1.end(); ++it1)
      cout << *it1 << endl;
   cout << endl << endl;

   cout << "List 1 back-to-front (should be original list 2 numbers):\n";
   for(it1 = lis1.r_begin(); it1 != lis1.r_end(); --it1)
      cout << *it1 << endl;
   cout << endl << endl;

   cout << "Copy of list 1 front-to-back (should be original list 1 numbers):\n";
   for(it1 = copy.begin(); it1 != copy.end(); ++it1)
      cout << *it1 << endl;
   cout << endl << endl;

   cout << "Copy of list 1 back-to-front (should be original list 1 numbers):\n";
   for(it1 = copy.r_begin(); it1 != copy.r_end(); --it1)
      cout << *it1 << endl;
   cout << endl << endl;
} // copy has been destroyed
*/

// finding out if the list still works after the copy is destroyed
/*
   cout << "Make sure list 1 still works after copy is destroyed:\n";
   cout << "List 1 front-to-back:\n";
   for(it1 = lis1.begin(); it1 != lis1.end(); ++it1)
      cout << *it1 << endl;
   cout << endl << endl;

   cout << "List 1 back-to-front:\n";
   for(it1 = lis1.r_begin(); it1 != lis1.r_end(); --it1)
      cout << *it1 << endl;
   cout << endl << endl;
*/

   return 0;
}
