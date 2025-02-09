#include <bits/stdc++.h>
#include <iostream>
using namespace std;
bool isPalindrome(int x) {
  vector<int> arr;
  for (int i = 0; x != 0; i++) {
    int val = x % 10;
    arr.push_back(val);
    x = x / 10;
  }
  int start = 0;
  int end = arr.size() - 1;
  while (start <= end) {
    if (arr[start] != arr[end]) {
      return false;
    }
    start++;
    end--;
  }
  return true;
}

int main() {
  int n = 12321;
  cout << isPalindrome(n);
  return 0;
}
