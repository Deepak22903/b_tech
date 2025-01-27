#include <bits/stdc++.h>
using namespace std;
#define MAX_SIZE 100

typedef struct arr {
  int *ar;
  int len;
  int size;
} arr;

void init(arr *a, int size) {
  a->ar = new int(size);
  a->len = 0;
  a->size = size;
}
void insert(arr *a, int p, int val) {
  for (int i = MAX_SIZE - 1; i > p; i--) {
    a->ar[i] = a->ar[i - 1];
  }
  a->ar[p] = val;
}
void insertatend(arr *a, int val) {
  if (a->len >= a->size)
    return;
  a->ar[a->len] = val;
  a->len++;
}
void remove(arr *a, int p) {
  for (int i = p; i < a->len - 1; i++) {
    a->ar[i] = a->ar[i + 1];
  }
  a->len--;
}
void print(arr a) {
  cout << endl << " array : ";
  for (int i = 0; i < a.len; i++) {
    cout << a.ar[i] << " ";
  }
  cout << endl << endl;
}

int search(arr a, int val) {

  for (int i = 0; i < a.len; i++) {
    if (a.ar[i] == val)
      return i;
  }
  return -1;
}

int main() {
  arr a;
  init(&a, 100);
  int p;
  while (1) {
    int choice;
    int val;
    cout << "1.Insert element in array " << endl
         << "2.Insert at particular Position" << endl
         << "3.Delete element from particular position" << endl
         << "4.search an element" << endl
         << "5.Print the array" << endl
         << "Enter the choice:";
    cin >> choice;
    switch (choice) {
    case 1:
      cout << "enter the value to be entered: ";
      cin >> val;
      insertatend(&a, val);
      break;
    case 2:
      cout << "enter the value to be entered: ";
      cin >> val;

      cout << "Enter the position : ";
      cin >> p;
      insert(&a, p, val);
      break;
    case 3:

      cout << "Enter the position of element to be deleted :";
      cin >> p;
      remove(&a, p);
      break;
    case 4:
      cout << "Enter the element to be searched: ";
      cin >> val;
      cout << "the position is: " << search(a, val) << endl;
      break;
    case 5:
      print(a);
      break;
    default:
      break;
    }
  }
}
