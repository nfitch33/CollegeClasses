/**
 * @file
 * @author Krerkkiat Chusap
 */
#include <iostream>
#include <string>
#include <vector>

#include "argmax.hpp"

using namespace std;

int main(int argc, char **argv) {
  string line;
  vector<float> values;

  // Reading a line as a float until EOF is reached.
  // EOF in a console on Linux is Ctrl+d, on Windows
  // it is Ctrl+z.
  while (std::getline(std::cin, line)) {
    values.push_back(stof(line));
  }

  auto max_index = argmax(values);
  cout << max_index << endl;
}