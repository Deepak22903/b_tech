#include <iostream>
using namespace std;

int sumofn(int n) {
  if (n < 10) {
    return n;
  }
  return (n % 10) + sumofn(n / 10);
}

int main() {
  int n;
  cout << "Enter a Number : ";
  cin >> n;
  int sum = sumofn(n);
  cout << "\n" << sum;
  return 0;
}
