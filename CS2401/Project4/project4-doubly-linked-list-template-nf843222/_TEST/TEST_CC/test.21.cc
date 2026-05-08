#include <iostream>
#include "dlist.h"

using namespace std;

int main() {
	dlist<int> list;

	list.rear_insert(8);
	dlist<int>::iterator it = list.begin();
	list.insert_after(it, 11);
	list.insert_after(it, 12);
	list.show();
	cout << endl;
}
