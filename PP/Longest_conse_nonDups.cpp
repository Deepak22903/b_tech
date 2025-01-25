#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<char> str;
bool is_dup(char ch) {
  if (str.empty()) {
    str.push_back(ch);
    return false;
  }
  for (int i = 0; i < str.size(); i++) {
    if (ch == str[i]) {
      str.erase(str.begin(), str.begin() + i + 1);
      str.push_back(ch);
      return true;
    }
  }
  str.push_back(ch);
  return false;
}

int lengthOfLongestSubstring(string s) {
  vector<int> sh;
  if (s.length() == 0)
    return 0;
  int len = 0;
  int max_len = 0;
  for (int i = 0; i < s.length(); i++) {
    if (!is_dup(s[i])) {
      len++;
    } else {
      len = str.size();
    }
    max_len = max(max_len, len);
  }
  return max_len;
}

int main() {
  string s = "pwwkew";
  int res = lengthOfLongestSubstring(s);
  cout << res << endl;
  return 0;
}
