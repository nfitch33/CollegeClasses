#include "Question7.h"
#include <array>
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
    arrayListType<int> array;
    array.setArray(1, 0);
    array.setArray(2, 1);
    array.setArray(3, 2);
    array.setArray(4, 3);
    array.setArray(5, 4);
    array.setArray(6, 5);
    array.setArray(7, 6);
    array.setArray(9, 7);
    array.setArray(15, 8);
    array.setArray(20, 9);

    cout << array.seqSearch(5) << endl;
    cout << array.seqSearch(19) << endl;
    cout << array.seqSearch(20, 10) << endl;
    return 0;
}