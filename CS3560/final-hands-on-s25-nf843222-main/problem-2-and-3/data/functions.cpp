/**
 * @author Student Name
 */
#include "functions.hpp"
#include <string>
#include <iostream>
using namespace std;


int countLine(string text){
    int lineCount = 0;
    for (char ch : text) {
        if (ch == '\n') {
            lineCount++;
        }
    }
    cout << lineCount << " lines" << endl;
    return lineCount;
}
int countChar(string text){
    int count = text.length();
    cout << count << " characters" << endl;
    return count;
}