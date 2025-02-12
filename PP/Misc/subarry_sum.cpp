class Solution {
public:
  int maxAscendingSum(vector<int> &nums) {
    int max = 0;
    int maxg = 0;
    for (int i = 0; i < nums.size(); i++) {
      if (nums[i + 1] > nums[i]) {
        max += nums[i];
      } else {
        max += nums[i];
        if (max > maxg) {
          maxg = max;
        }
        max = 0;
      }
    }
    return maxg;
  }
};
