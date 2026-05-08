#include <iostream>
using namespace std;

void pretty(){
    static int x = 0;
    x++;
    for(int i = 0; i < 5; i++){
        cout << '*';
    }
    cout << endl;
}

main(){
    pretty();
}