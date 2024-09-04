#include <bits/stdc++.h>
#include <iostream>
using namespace std;

void star(int n) {
  for (int i = 0; i < n; i++) {
    for (int j = i; j < i; j++) {
      cout << "* ";
    }
    cout << endl;
  }
}

int main() {
  int n = 0;
  cout << "Enter lines: ";
  cin >> n;
  star(n);
  return 0;
}
