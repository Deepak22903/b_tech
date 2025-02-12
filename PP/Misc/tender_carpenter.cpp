#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool check_tri(vector<int> arr) {
  if (arr.size() < 3)
    return false; // At least 3 sides needed for a triangle

  sort(arr.begin(), arr.end()); // Sort array

  for (int i = 2; i < arr.size(); i++) {
    if (arr[i - 2] + arr[i - 1] > arr[i]) {
      return true; // Triangle inequality holds
    }
  }

  return false;
}

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int num;
    cin >> num;
    vector<int> arr(num);
    for (int j = 0; j < num; j++) {
      cin >> arr[j];
    }
    bool res = check_tri(arr);
    cout << (res ? "YES" : "NO") << endl;
  }
  return 0;
}
