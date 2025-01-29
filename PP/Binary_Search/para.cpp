#include <bits/stdc++.h>
#include <iostream>
using namespace std;

bool para(string s) {
  stack<char> cs;
  for (int i = 0; i < s.length(); i++) {

    if (s[i] == '(' || s[i] == '{' || s[i] == '[') {
      cs.push(s[i]);
    } else {
      if (s[i] == ')' && cs.top() == '(' || s[i] == ']' && cs.top() == '[' ||
          s[i] == '}' && cs.top() == '{') {
        cs.pop();
      }
    }
  }

  if (cs.empty()) {
    return true;
  } else
    return false;
}

int main() {
  string s = "";
  cout << "Enter String : ";
  cin >> s;
  bool res = para(s);
  cout << res << endl;
  return 0;
}
