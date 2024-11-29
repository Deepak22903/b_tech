#include <iostream>
#include <vector>
using namespace std;

int search(vector<int> nums, int target) {
  int low = 0;
  int high = nums.size() - 1;
  while (low <= high) {
    int mid = low + (high - low) / 2;
    if (nums[mid] == target) {
      return mid;
    } else if (nums[mid] < target) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  return -1;
}

int main() {
  vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 22, 33, 44};
  int target = 22;
  int index = search(nums, target);
  cout << "target found at index " << index;
  return 0;
}
