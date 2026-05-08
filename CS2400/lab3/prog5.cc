/*
 *      Author: Nathaniel Fitch
 *      Date: 09/15/2023
 *      Description: Error in the program stopped correct usuage of math to solve temperature in two different degree types. Edited and Fixed the program to
 *                   print correct numbers, also added iomanip to get setprecision, so the numbers go to one decimal.
 */

#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;

int main()
{
   double ctof;  // equivalent Celsius temperature
   double ftoc;  // equivalent Fahrenheit temperature.
 
   double fah = 56;  //declare and initialize at the same time - page 48
   double cel = 20;

   ctof = ((9 * cel)/5) + 32;
   ftoc = ((5 * (fah -32))/9);

   cout << cel << " degrees Celsius in Fahrenheit is " << fixed << setprecision(1) << ctof << endl;
   cout << fah << " degrees Fahrenheit in Celsius is " << fixed << setprecision(1) << ftoc << endl;

   return (EXIT_SUCCESS);
}
