#include "utils.hpp"

#include <string>
#include <vector>

using namespace std;

vector<string> split_by(const string &source, const string &delim) {
  vector<string> tokens;

  size_t pos = 0;
  size_t last_pos = 0;
  string token;
  while ((pos = source.find(delim, last_pos)) != string::npos) {
    token = source.substr(last_pos, pos - last_pos);
    tokens.push_back(token);
    last_pos = pos + delim.length();
  }
  token = source.substr(last_pos);
  tokens.push_back(token);
  return tokens;
}

string unlines(const vector<string> &lines) {
  string result = "";
  for (auto l : lines) {
    result += l + "\n";
  }
  return result;
}