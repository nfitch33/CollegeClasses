/*      File: git-lab-program.cc
 *      Author: Nathaniel Fitch
 *      Date: 10/20/2023
 *      Description: Using a created file, the program will encrypt the message using a ceaser cypher. Also the program will be able to decrypt the message.
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>  // All the include statements
#include <fstream>
using namespace std;

bool getMessage(int key);
bool displaymenu(int key);
bool getEncrypt(int key);
int getKey(int &key);      // All global variables used throughout the whole program
ifstream inStream;
ofstream outStream;
string input;
string output;
char ch;
string whole;

int main(int argc, char const *argv[]) {
    int key;
    key = 3;
    int choice;    // Sets the key to 3 and also allows choice to be used
    choice = 0;
    displaymenu(key);

    do  {
        if (choice == 1) {  // If choice is 1, your able to set the key that shifts numbers to a number of your choosing, 1-10
            getKey(key);
        }
        else if (choice == 2) { // Grabs the first file to get a message then encrypts it in a second file
            if (getMessage(key) == false){
                cout << "Unable to find files" << endl;
                exit (0);
            }
            else {
                cout << "Message Encrypted" << endl;
                displaymenu(key);
            }
        }
        else if (choice == 3) {    // Grabs the encrypted file and decrypts it then uploads it to a chosen file
            if (getEncrypt(key) == false){
                cout << "Unable to find files" << endl;
                exit (0);
            }
            else {
                cout << "Message Decrypted" << endl;
                displaymenu(key);
            }
        }
        else if (choice > 4) {   // If the number is over 4 it will warn the user
            cout << "Number 1-4" << endl;
        }
        cin >> choice;
    } while (choice != 4);
    return(0);
}


bool displaymenu(int key) { // Function that shows user what options they have

        cout << "Pick one of the following: " << endl;
        cout << "1. Set the shift key, current is " << key << endl;
        cout << "2. Encrypt a file" << endl;
        cout << "3. Decrypt a file" << endl;
        cout << "4. Quit" << endl;
        return (true);
}
bool getMessage(int key){  // Function for getting original message and encrypting it
    whole = ""; // Makes sure it won't repeat any previous information in the variable
    cout << "Enter the input file name: ";
    cin >> input;
    cout << "Location of encrypted message: ";
    cin >> output;
    inStream.open(input);
    while (inStream.get(ch)){
        ch = ch + key;
        whole = whole + ch;
    }
    inStream.close();
    outStream.open(output);
    outStream << whole;
    outStream.close();
    return true;
}
bool getEncrypt(int key){  // Function for getting encrypted message and decrypting it
    whole = ""; // Makes sure it won't repeat any previous information in the variable
    cout << "Enter the encrypted file name: ";
    cin >> input;
    cout << "Location of the decrypted message: ";
    cin >> output;
    inStream.open(input);
    while (inStream.get(ch)){
        ch = ch - key;
        whole = whole + ch;
    }
    inStream.close();
    outStream.open(output);
    outStream << whole;
    outStream.close();
    return true;
}
int getKey(int &key){   // Function that allows user to change what the key number will be
            cout << "What would you like the key number to be? " << endl;
            cin >> key;
            while (key < 1 || key > 10) {
                cout << "Key must be between 1 & 10, Enter a different number" << endl;
                cin >> key;
            }
            cout << "New key is " << key << endl;
            return key;
}