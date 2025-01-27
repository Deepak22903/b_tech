#include <iostream>

using namespace std;

class Stack {
private:
  int top;
  char arr[100];

public:
  Stack() { top = -1; }

  void push(char ch) {
    if (top >= 99) {
      cout << "Stack Overflow" << endl;
      return;
    }
    arr[++top] = ch;
    return;
  }

  void pop() {
    if (top < 0) {
      cout << "No Elements to pop" << endl;
      return;
    }
    top--;
    return;
  }

  char topelem() { return arr[top]; }
  bool empty() {
    if (top < 0) {
      return true;
    }
    return false;
  }
};

int main() {
  string ins = "";
  cin >> ins;
  Stack s;

  for (int i = 0; i < ins.length(); i++) {
    if (ins[i] == '(' || ins[i] == '{' || ins[i] == '[') {
      s.push(ins[i]);
    } else if (ins[i] == ')' && !s.empty() && s.topelem() == '(') {
      s.pop();
    } else if (ins[i] == '}' && !s.empty() && s.topelem() == '{') {
      s.pop();
    } else if (ins[i] == ']' && !s.empty() && s.topelem() == '[') {
      s.pop();
    } else {
      cout << "Not matching!" << endl;
      return 0;
    }
  }

  if (s.empty()) {
    cout << "Matching!" << endl;
  } else {
    cout << "Not matching!" << endl;
  }

  return 0;
}
