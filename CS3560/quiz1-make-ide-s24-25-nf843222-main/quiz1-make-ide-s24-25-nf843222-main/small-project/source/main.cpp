#include <string>
#include <iostream>

#include "split_by.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    const string text;

    if (argc == 1) {
        cout << "usage: ./split-by [--version] TEXT DELIM" << endl << endl;
        cout << "The program will split the TEXT with DELIM." << endl;
        cout << "If DELIM is not provided, a single space (' ') will be used." << endl;
        cout << "The resulted tokens will be printed one per line." << endl;
    } else if (argc >= 2) {
        // --version or TEXT without DELIM
        if (string(argv[1]) == "--version") {
            cout << "0.0.1" << endl;
        } else if (argc == 2) {
            for (auto token : split_by(argv[1], " ")) {
                cout << token << endl;
            }
        } else {
            // TEXT with DELIM.
            for (auto token : split_by(argv[1], argv[2])) {
                cout << token << endl;
            }
        }
    } 
}
