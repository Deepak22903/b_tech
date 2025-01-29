#include <iostream>
#include <vector>
using namespace std;

int main() {
  vector<vector<int>> v;
  v.push_back({1, 6});
  v.push_back({2, 4});

  for (auto it = v.begin(); it != v.end(); it++) {
    for (auto itr = it->begin(); itr != it->end(); itr++) {
      cout << *itr << " ";
    }
    cout << endl;
  }
}
