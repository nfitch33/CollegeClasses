#include <iostream>
#include "linked_list.h"
using namespace std;

int main(int argc, char** argv) {
  LinkedList<int> list;
  char grab = '!';
  char x = '0';
  while(grab != 'q' && grab != 'Q'){

    // cout << "What would you like to do: " << endl;
    // cout << "a = add to front" << endl;
    // cout << "d = delete front" << endl;
    // cout << "p = print list" << endl;
    // cout << "r = reverse list" << endl;
    // cout << "q = quit" << endl;
    cin >> grab;

    if(grab == 'A' || grab == 'a'){
      // cout << "NUMBER: ";
      cin >> x;
      list.push_front(x);
    }

    else if(grab == 'D' || grab == 'd'){
      list.pop_front();
    }

    else if(grab == 'P' || grab == 'p'){
      list.print();
    }

    else if(grab == 'R' || grab == 'r'){
      list.reverse();
    }
  }
  // cout << "Have a great day!" << endl;
}
