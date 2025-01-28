#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

int missing(vector<int> arr) {
  int start = 0;
  int end = arr.size() - 1;
  while (start <= end) {
    int mid = start + (end - start) / 2;
    if (arr[mid] != mid) {
      end = mid - 1;
    } else {
      start = mid + 1;
    }
  }
  return start;
}

int main() {
  vector<int> arr = {0, 1, 2, 4, 5, 6, 7, 8, 9};
  int res = missing(arr);
  cout << res << endl;
  return 0;
}
