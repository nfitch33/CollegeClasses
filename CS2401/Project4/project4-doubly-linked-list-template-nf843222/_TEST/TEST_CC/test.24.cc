#include <iostream>
#include "dlist.h"

using namespace std;

int main() {
	dlist<int> list;

	for(int i = 0; i < 10; ++i) {
		list.rear_insert(i);
	}
	dlist<int>::iterator it = list.r_begin();
	list.remove(it);
	list.show();
	cout << endl;
}
