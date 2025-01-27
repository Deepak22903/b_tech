#include <iostream>
#include <vector>
using namespace std;

void insert_elem(vector<int> &arr) {
  int elem, pos;
  cout << "Element : ";
  cin >> elem;
  cout << "\nPosition : ";
  cin >> pos;
  arr.insert(arr.begin() + pos, elem);
  return;
}

void delete_elem(vector<int> &arr) {
  int pos;
  cout << "\nPosition : ";
  cin >> pos;
  arr.erase(arr.begin() + pos);
  return;
}

void search_elem(vector<int> &arr) {
  int elem;
  cout << "\nElement : ";
  cin >> elem;
  for (int i = 0; i < arr.size(); i++) {
    if (arr[i] == elem) {
      cout << "Element found at position " << i << " ." << endl;
      return;
    }
  }
  cout << "Element not Found";
  return;
}

void display(vector<int> &arr) {
  for (int i = 0; i < arr.size(); i++) {
    cout << arr[i] << endl;
  }
  return;
}

int main() {
  vector<int> arr;
  while (1) {
    int choice;
    cout << "1.Insert\n2.Delete\n3.Search\n4.Display\nChoice> ";
    cin >> choice;
    if (choice == 1) {
      insert_elem(arr);
    } else if (choice == 2) {
      delete_elem(arr);
    } else if (choice == 3) {
      search_elem(arr);
    } else {
      display(arr);
    }
  }
}
