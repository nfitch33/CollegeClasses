/*
*  program: lab10.cc 
*   Name : Nathaniel Fitch
*   Date : 11/3/2023
*   Email : nf843222@ohio.edu
*   Description: purpose of this lab is to create two arrays that will read prices and objects from a file, sort them from greatest to least and then output the information
*/
#include <iostream>
#include <iomanip>
#include <cstdlib>  // All the include statements
#include <fstream>
using namespace std;


ifstream inStream;

int main(int argc, char const *argv[]) {

    string objects[6];
    string prices[6];
    string priceSTRING; // Variable names throughout code
    string objectsSTRING;
    string constant;

    inStream.open(argv[1]); // opens the first file to get strings, this will be data1.txt

    for(int z = 0; z < 6; z++){
        getline(inStream, priceSTRING);
        prices[z] = priceSTRING;    // puts the information into the array.
    }

    inStream.close(); // closes current ifStream to make room for a second one
    inStream.open(argv[2]); // opens second file, data2.txt

    for(int p = 0; p < 6; p++){
        getline(inStream, objectsSTRING); // puts the information into the array
        objects[p] = objectsSTRING;
    }
    inStream.close(); // closes the ifstream

    // This will sort the prices in order from least to greatest. If the price is larger it will stay furthest to the left, and also the corresponding object
       // in the other array will also swap to keep it in order.
    for(int x = 0; x < 6; x++){
        constant = prices[x];
        for (int y = 0; y < 6; y++){
            if (prices[y] > constant){
                swap(prices[y], prices[x]);
                swap(objects[y], objects[x]);
            }
            else if (prices[y] == constant){
                swap (prices[y], prices[x]);
                swap (objects[y], objects[x]);
            }
        }
        // This is needed because it reads the first two characters to determine which is larger since thye are strings. this swaps $90 and $3500
        swap(prices[4], prices[5]);
        swap(objects[4], objects[5]);
    }
    // Puts all information into the terminal
    cout << "The most expensive part is " << objects[5] <<  " ($" << prices[5] << ")" << endl;
    cout << "The second most expensive part is " << objects[4] <<  " ($" << prices[4] << ")" << endl;
    cout << "The third expensive part is " << objects[3] <<  " ($" << prices[3] << ")" << endl;
    cout << "The fourth expensive part is " << objects[2] <<  " ($" << prices[2] << ")" << endl;
    cout << "The second least expensive part is " << objects[1] <<  " ($" << prices[1] << ")" << endl;
    cout << "The least expensive part is " << objects[0] <<  " ($" << prices[0] << ")" << endl;
}