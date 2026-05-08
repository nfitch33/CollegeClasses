#include <iostream>
#include <cstdlib>
using namespace std;
int main(){
    size_t capacity = 5;
    size_t used = 0;
    int* p = new(int);
    p = new int[capacity];

    for(size_t i = 0; i < 25; i++){
        p[used] = rand();
        // cout << p[used] << endl;
        used++;
        if (used == capacity){
           capacity += 5;
           int* temp = new int[capacity];
           for(int i = 0; i < used; i++){
            temp[i] = p[i];
            temp[2] = 0;
            for(int i = 0; i < 4; i++){
        cout << temp[i] << endl;
    }
           }
        }
        
    }
    
    delete p;
    return -1;
}