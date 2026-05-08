/*
/ Name: Nathaniel Fitch
/ Lab: CS 2400 - Lab3
/ Date: 9/15/2023
/ Description: Step 2 of Completing Lab, Have to reagrange code to make it look neat, and readable.
*/

#include<iostream> 
#include<cstdlib>
using namespace std;
const int INT1 = 15;
const int INT2 = 20; 

int main()
{
    cout << "Sum of " << INT1 << " and " << INT2 << " is " << INT1 + INT2 << endl;
    cout << "Product is " << INT1 * INT2 << endl;
    if (INT1 < INT2) {
        cout<<INT2 <<"is bigger";
    }   
    else {
        cout << INT1 << " is bigger"; 
    }
    return (EXIT_SUCCESS);
}
