#include <iostream>
#include "dlist.h"

using namespace std;

int main() {
	dlist<int> list;
	list.rear_insert(16);
	list.front_remove();
	list.show();
	cout << endl;
}
