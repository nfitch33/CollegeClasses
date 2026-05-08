#include <iostream>
#include "dlist.h"

using namespace std;

int main() {
	dlist<int> list;
	list.front_remove();
	list.show();
	cout << endl;
}
