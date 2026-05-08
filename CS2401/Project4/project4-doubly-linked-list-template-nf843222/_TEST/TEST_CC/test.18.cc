#include <iostream>
#include "dlist.h"

using namespace std;

int main() {
	dlist<int> list;

	for(int i = 0; i < 10; ++i) {
		list.rear_insert(i);
	}
	dlist<int>::iterator it = list.begin();
	it++;
	it++;
	it++;
	list.insert_before(it, 11);
	list.insert_before(it, 12);
	list.show();
	cout << endl;
}
