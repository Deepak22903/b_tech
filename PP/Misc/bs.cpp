#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

int search(vector<int> &nums, int target) {
  int mid = nums.size() / 2;
  if (nums[mid] == target) {
    return mid;
  } else if (nums[mid] < target) {
    mid = (mid)
  }
}

void main() {
  vector<int> arr = {1, 2, 3, 5, 6, 9};
  int target = 2;
  cout << search(arr, target);
}
