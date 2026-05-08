/*      File: git-lab-program.cc
 *      Author: Nathaniel Fitch
 *      Date: 10/20/2023
 *      Description: Using a created file, the program will encrypt the message using a ceaser cypher. Also the program will be able to decrypt the message.
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
using namespace std;

bool displaymenu(int key);
ifstream m;
ofstream e;

int main(int argc, char const *argv[]) {
    int key;
    int choice;
    choice = 0;
    key = 3;
    char ch;
    string whole;
    string input;
    string output;
    cout << "Enter Input location surrounded by """;
    cin >> input;
    cout << "Enter Output location surrounded by """;
    cin >> output;
    m.open(input);
    while(m.get(ch)){
        whole = whole + ch;
    }
    m.close();
    cout << whole << endl;
    e.open(output);
    e << "4444";
    e.close();
}


bool displaymenu(int key) {
        cout << "Pick one of the following: " << endl;
        cout << "1. Set the shift key, current is " << key << endl;
        cout << "2. Encrypt a file" << endl;
        cout << "3. Decrypt a file" << endl;
        cout << "4. Quit" << endl;
        return (true);
}