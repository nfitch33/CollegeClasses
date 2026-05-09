/**
 * @author Nathaniel Fitch
 */
#include <iostream>
#include <fstream>
#include "functions.hpp"

using namespace std;

int main(int argc, string *argv[]) {
    string input = "";
    if(argc == 0){
        cout << "Error" << endl;
    }
    else{
        int x = 1;
        while(x != 0){
            argv[x].getline(argv[x],input);
            x--;
        }
    }


    return 0;
}