#include <iostream>
#include "dlist.h"

using namespace std;

int main() {
	dlist<int> list;

	for(int i = 0; i < 10; ++i) {
		list.rear_insert(i);
	}
{	
	dlist<int> copy = list;

	cout << "copy exists, copy list:" << endl;
	copy.show();
	cout << endl;
}
	cout << "copy destroyed, original list:" << endl;
	list.show();
	cout << endl;
}
