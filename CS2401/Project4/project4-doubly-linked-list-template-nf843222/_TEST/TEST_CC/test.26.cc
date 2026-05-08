#include <iostream>
#include "dlist.h"

using namespace std;

int main() {
	dlist<int> list;

	dlist<int>::iterator it = list.begin();
	list.remove(it);
	list.show();
	cout << endl;
}
