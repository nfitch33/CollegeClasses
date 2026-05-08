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
using namespace std;

ifstream inStream;
ofstream outStream;

int main(int argc, char const *argv[]) {
    inStream.open(argv[1]);
    outStream.open(argv[2]);
    string text;
    char ch;
    for (int x = 0; x <= 19; x++){
        getline(inStream, text);
        for (int y = 0; y < text.length(); y++){
            ch = text.at(y);
            if (ch >= 'a' && ch <= 'z'){
                text.at(y) = ch - 32;
            }
            else if (ch <= '9' && ch >= '0'){
                text.at(y) = '*';
            }
            else {
                text.at(y) = ch;
            }
        }
        outStream << text;
        outStream << endl;
    }
}