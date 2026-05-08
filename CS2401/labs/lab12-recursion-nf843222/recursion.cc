#include "recursion.h"
#include <string>
using namespace std;
void counting(int n){
    if(n >= 0){
        if(n % 2 == 0){
            for(int x = 0; x < n; x+=2){
                cout << x << endl;
            }
            cout << n << endl;
        }
        else{
            for(int x = 0; x < n; x+=2){
                cout << x << endl;
            }
        }
    }
    return;
}

void reversing(std::string& s, int start, int end){
    cout << s << endl;
    if(start < 0){
        return;
    }
    else{
        string h = "";
        string t = "";
        string c = "";
        for(int x = start; x < end; x++){
            h += s.at(x);
        }
        h += s.at(end);
        for(size_t x = end + 1; x <= s.length() - 1; x++){
            c += s.at(x);
        }
        if(start == 0){
            t = "";
        }
        else{
            t = s.substr(0, start);
        }
        for(size_t x = h.length() - 1; x > 0; x--){
            t += h.at(x);
        }
        t += h.at(0);
        s = t;
        s += c;
    }
}