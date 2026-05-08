#include <iostream>
#include "dlist.h"

using namespace std;

int main() {
	dlist<int> list;
	dlist<int>::iterator it;

	for(int i = 0; i < 10; ++i) {
		list.rear_insert(i);
	}

	for(it = list.r_begin(); it != list.r_end(); --it) {
		cout << *it << endl;
	}
	cout << endl;
}
