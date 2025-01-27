
#include <bits/stdc++.h>
using namespace std;

int binarySearch(vector<int> arr) {
  int low = 0;
  int high = arr.size() - 1;

  while (low <= high) {
    int mid = low + (high - low) / 2;

    if (arr[mid] != mid) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }
  return low;
}

int main() {
  vector<int> arr = {0, 1, 2, 4, 5, 6};
  cout << "The missing element is " << binarySearch(arr) << endl;
  return 0;
}
