#include <iostream>
#include "dlist.h"

using namespace std;

int main() {
	dlist<int> list;

	list.rear_insert(8);
	dlist<int>::iterator it = list.begin();
	list.remove(it);
	list.show();
	cout << endl;
}
