#include <iostream>
#include <ostream>
#include <string>
#include <vector>

int main() {
  int tc = 0;
  std::cin >> tc;
  std::vector<std::string> s(tc);
  for (int i = 0; i < tc; i++) {
    std::cin >> s[i];
  }

  for (int i = 0; i < tc; i++) {
    std::string bin = s[i];
    int cnt = 0;
    for (int j = 0; j < bin.length(); j++) {
      if (bin[j] == '1') {
        cnt++;
      }
    }
    std::cout << cnt << std::endl;
  }

  return 0;
}
