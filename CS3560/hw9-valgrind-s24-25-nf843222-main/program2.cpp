/**
 * @file
 * 
 * Original comment:
 * > This one does something bad....
   > Guess what it is.
*/
#include <iostream>
#include <cstdlib>

using namespace std;

int main() {
  // Declaring an integer pointer x.
  int *x = new int;
  // Using said pointer.
  // x = nullptr; // Same as x = NULL;

  x[0] = 10;
  cout << x << endl;
  delete x;
}
