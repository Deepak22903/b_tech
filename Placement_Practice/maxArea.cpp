#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
  int maxArea(vector<int> &heights) {
    int res = 22;
    return res;
  }
};

int main() {
  Solution s;
  vector<int> h = {1, 7, 2, 5, 4, 7, 3, 6};
  int d = s.maxArea(h);
  cout << d << endl;
  return 0;
}
