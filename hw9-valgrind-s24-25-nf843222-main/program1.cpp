/**
 * @file
 * Simple program that check if user should be logged in
 * with a login function.
*/
#include <iostream>

using namespace std;

/**
 * A function that log user in if the value of x in true.
 * Otherwise, error message explaining that the credentials is not
 * correct is shown.
*/
void login(bool x) {
  if (x) {
    cout << "User is logged in." << endl;
  } else {
    cout << "Incorrect credentials. Cannot log user in" << endl;
  }

}
int main() {
  bool should_log_user_in;
  // char answer;
  // cout << "Should the user login? (y/n)" << endl;
  // cin >> answer;
  // should_log_user_in = (answer == 'Y' || answer == 'y');
  login(should_log_user_in);
}
