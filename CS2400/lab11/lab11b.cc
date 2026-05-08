/**
 *   @file: Lab11.cc
 * @author: Nathaniel Fitch
 *   @date: 11/11/2023
 *  @brief: The following project allows the user to send in a text file, that will encrypt the date of birth and social sequrity numbers to astericks.
 *          The names will be set to uppercase only and other characters remain the same.
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <cctype>
#include <vector>
#include <string>
using namespace std;

const int SIZE = 10;
double a_list[] = {3.2,4.6,7.0,12.5,8.3,9.1}; 
int nums[SIZE];
char vowels[] = {'A','E','I','O','U'};
string name[SIZE];
float values[SIZE];
int i = 3;

int main(int argc, char const *argv[]) {
     cout << setfill('-') << left << setw(5)<< a_list[0] << endl;;
}
