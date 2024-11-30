#include <iostream>
#include <vector>

int search(std::vector<int> num, int target) {
  int low = 0;
  int high = num.size() - 1;
  while (low <= high) {
    int mid = low + (high - low) / 2;
    if (num[mid] == target) {
      return mid;
    } else if (num[mid] < target) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  return -1;
}

int main() {
  std::vector<int> num = {1, 2, 3, 4, 4, 5, 6, 7, 7, 8, 8, 8, 9};
  int target = 0;
  std::cout << "Enter a number to search : ";
  std::cin >> target;
  int index = search(num, target);
  std::cout << "The number is at index " << index << std::endl;
  return 0;
}
