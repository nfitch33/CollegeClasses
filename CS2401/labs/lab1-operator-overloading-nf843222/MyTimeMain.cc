#include "MyTime.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>

using namespace std;

int main(int argc, char const *argv[]){
    MyTime t1;
    MyTime t2;
    cout << "Enter First time: ";
    cin >> t1;
    cout << endl;
    cout << "Enter Second time: ";
    cin >> t2;
    cout << endl;

    cout << t1 + t2 << endl;
    cout << t1 - t2 << endl;
    cout << t1 * 3 << endl;
    cout << t1 / 2 << endl;
    if (t1 <= t2){
        cout << "fisrt time is less than or equal to second time" << endl;
    }
    else {
        cout << "second time is less than first time" << endl;
    }
    return 0;
}