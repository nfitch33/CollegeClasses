#include<iostream>
using namespace std;
int var = 2401;
    main(){
            int* p = new(int);
            *p = 2401;
            cout << *p << " is stored at: " << p << endl;
            for (size_t i = 0; i < 10; i++){
                int j = 1;
                cout << j << endl;
                ++(p);
                cout << *p << " is stored at " << p << endl;
                j++;
            }
            delete p;
    }
