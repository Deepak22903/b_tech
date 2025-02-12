#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
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
};
