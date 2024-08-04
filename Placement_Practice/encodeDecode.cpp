#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  vector<int> size1;
  string encode(vector<string> &strs) {
    string res = "";
    for (int i = 0; i < strs.size(); i++) {
      size1.push_back(strs[i].size());
      res = res.append(strs[i]);
    }

    return res;
  }

  vector<string> decode(string s) {
    vector<string> result;
    int start = 0;
    for (int i = 0; i < size1.size(); i++) {
      int len = size1[i];
      string value = s.substr(start, len);
      result.push_back(value);
      start += len;
    }

    return result;
  }
};

int main() {
  Solution solution;

  // Sample input
  vector<string> input = {"hello", "world", "this", "is", "test"};

  // Encoding
  string encoded = solution.encode(input);
  cout << "Encoded: " << encoded << endl;

  // Decoding
  vector<string> decoded = solution.decode(encoded);
  cout << "Decoded: ";
  for (const string &str : decoded) {
    cout << str << " ";
  }
  cout << endl;

  return 0;
}
