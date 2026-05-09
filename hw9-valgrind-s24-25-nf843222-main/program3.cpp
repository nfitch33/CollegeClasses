/**
 * @file
 * @author Krerkkiat Chusap
 * 
 * A program designed to trigger Valgrind's error.
*/
#include <iostream>
#include <string>

using namespace std;

struct BankAccount {
    string name;
    float balance;

    BankAccount() : name(""), balance(0.0f) {}
    BankAccount(string name, float balance) : name(name), balance(balance) {}
};

void show_account(const BankAccount *acc) {
    cout << "Account: " << acc->name << " (balance: " << acc->balance << ")" << endl;
}

int main() {
    BankAccount *acc1, *acc2;
    acc1 = new BankAccount("OU IEEE", 10000.0f);
    acc2 = new BankAccount("OU ACM", 10000.0f);

    show_account(acc1);
    show_account(acc2);

    delete acc1;
    delete acc2;

    return EXIT_SUCCESS;
}
