#include "numlist.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cctype>



using namespace std;

int main(int argc, char const *argv[]){
    ifstream ins;
    ofstream outs;
    NumList n;

    string file_name = "";
    string file_test = "";
    int num1, num2, num3;

    cout << "What is the name of your file" << endl;
    cin >> file_name;
    ins.open(file_name.c_str());

    if (ins.fail()){
        cout << "Program could not be opened" << endl;
        return -1;
    }

    n.load_from_file(ins);
    n.i_sort();

    num1 = 113;
    num2 = 763;
    num3 = 23508;

    n.insert(num1);
    n.insert(num2);
    n.insert(num3);

    n.i_sort();
    cout << "----------------" << endl;

    int find = file_name.find('.');
    file_name.insert(find, "sorted");

    outs.open(file_name.c_str());
    n.save_to_file(outs);
}
