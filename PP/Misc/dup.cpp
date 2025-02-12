#include <bits/stdc++.h>
using namespace std;
bool hasDuplicate(vector<int> &nums) {
  int count = 0;
  for (int i = 0; i < nums.size(); i++) {
    for (int j = 0; j < nums.size(); j++) {
      if (nums[i] == nums[j]) {
        count++;
      }
    }
  }
  cout << count << endl;
  cout << nums.size() << endl;

  if (count > nums.size()) {
    return true;
  } else {
    return false;
  }
  return true;
}

int main() {
  vector<int> nums = {1, 2, 3};
  bool res = hasDuplicate(nums);
  cout << res << endl;
  return 0;
}
