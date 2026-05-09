#include <iostream>
#include <vector>

using namespace std;

vector<int> calculate_fibonacci(const int n) {
    vector<int> results;
    int a = 1;
    int b = 1;
    int tmp;

    if (n >= 1) {
        results.push_back(1);
    }
    if (n >= 2) {
        results.push_back(1);
    }

    for (int i = 2; i < n; i++) {
        tmp = b;
        b = a + b;
        a = b;
        results.push_back(b);
    }

    return results;
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        int n = atoi(argv[1]);
        vector<int> results = calculate_fibonacci(n);
        for (auto i : results) {
            cout << i;
        }
    } else {
        cout << "usage: " << argv[0] << " <number>" << endl;
    }
}