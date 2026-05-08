#include <iostream>
#include "dlist.h"

using namespace std;

int main() {
	dlist<int> list;
	list.rear_insert(16);
	list.rear_remove();
	list.show();
	cout << endl;
}
