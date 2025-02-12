#include <iostream>
using namespace std;

void fragments(int s, int m, int h) {
  int size = s - h;
  int offset = 0;
}

int main() {
  int size = 0;
  int mtu = 0;
  int head = 0;
  cout << "Enter data size: ";
  cin >> size;
  cout << "\n Enter MTU: ";
  cin >> mtu;
  cout << "\n Enter header size: ";
  cin >> head;
  fragments(size, mtu, head);
  return 0;
}
