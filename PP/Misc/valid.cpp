#include <bits/stdc++.h>
using namespace std;

bool isValid(string s) {
  stack<char> char_stack;
  for (int i = 0; i < s.length(); i++) {
    if (char_stack.empty()) {
      char_stack.push(s[i]);
      continue;
    }
    if (char_stack.top() == '(' && s[i] == ')') {
      char_stack.pop();
      continue;
    }
    if (char_stack.top() == '[' && s[i] == ']') {
      char_stack.pop();
      continue;
    }
    if (char_stack.top() == '{' && s[i] == '}') {
      char_stack.pop();
      continue;
    }
    char_stack.push(s[i]);
  }
  return char_stack.empty();
}

int main() {
  string s = "[]";
  bool res = isValid(s);
  cout << res << endl;
  return 0;
}
