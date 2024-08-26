#include <bits/stdc++.h>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
  int maxArea(vector<int> &heights) {
    vector<int> areas;
    int res = 0;
    int start = 0;
    int end = heights.size() - 1;
    int length = 0;
    int breadth = heights.size() - 1;
    while (start < end) {
      if (heights[start] > heights[end]) {
        length = heights[end];
      } else
        length = heights[start];
      res = length * breadth;
      areas.push_back(res);
      breadth -= 2;
      start++;
      end--;
    }
    sort(areas.begin(), areas.end());
    int area = areas.back();
    return area;
  }
};

int main() {
  Solution s;
  vector<int> h = {1, 7, 2, 5, 4, 7, 3, 6};
  int d = s.maxArea(h);
  cout << d << endl;
  return 0;
}
