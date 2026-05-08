#include <iostream>
#include <string>

/**
 * Problem One: Write a recursive function, called counting, 
 * that receives a single parameter which should always be a 
 * positive number and then prints all the even numbers from 
 * 0 up to, and including the number that was passed in, if 
 * that number is even, or one less than the number passed 
 * in if it is odd. (“Up to” means that you start with the 
 * smallest number and end with the largest number.)
*/
void counting(int n);

/**
 * Problem Two: In this one, the recursive function takes a 
 * string and two arguments that are array indexes. The program 
 * then reverses all the characters within the array indexes, 
 * so given s= “abcdef” and the numbers 2 and 5 the printed 
 * string should be “abfedc”. Remember to pass the string by 
 * reference and that the base case needs to consider the 
 * possibility of the two indexes crossing each other. 
*/
void reversing(std::string& s, int start, int end);