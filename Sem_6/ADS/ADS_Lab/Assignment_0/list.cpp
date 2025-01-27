#include <bits/stdc++.h>
using namespace std;

typedef struct node {
  int val;
  node *next;
  node(int value) : val(value), next(nullptr) {}
} node;

typedef struct ll {
  node *head;
} ll;

void init(ll *l) { l->head = nullptr; }

void insert(ll *l, int val) {
  if (l->head == nullptr) {
    l->head = new node(val);
    return;
  }
  node *p = l->head;
  while (p->next) {
    p = p->next;
  }
  p->next = new node(val);
}

void print(ll l) {
  node *p = l.head;
  while (p) {
    cout << p->val << " ";
    p = p->next;
  }
  cout << endl;
}

void insert(ll *l, int pos, int val) {
  if (pos == 0) {
    node *new_node = new node(val);
    new_node->next = l->head;
    l->head = new_node;
    return;
  }
  node *p = l->head;
  for (int i = 0; i < pos - 1; i++) {
    if (p == nullptr)
      return;
    p = p->next;
  }
  node *new_node = new node(val);
  new_node->next = p->next;
  p->next = new_node;
}

void del(ll *l, int pos) {
  node *p = l->head;
  if (pos == 0) {
    l->head = p->next;
    delete p;
    return;
  }
  for (int i = 0; i < pos - 1; i++) {
    p = p->next;
  }
  node *q = p->next;
  p->next = q->next;
  delete q;
}

int search(ll l, int val) {
  node *p = l.head;
  int i = 0;
  while (p) {
    if (p->val == val) {
      return i;
    }
    i++;
    p = p->next;
  }
  return -1;
}

int main() {
  ll l;
  init(&l);

  int choice;
  do {
    cout << "\n--- Menu ---\n";
    cout << "1. Insert at end\n";
    cout << "2. Insert at position\n";
    cout << "3. Delete at position\n";
    cout << "4. Search value\n";
    cout << "5. Print list\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1: {
      int value;
      cout << "Enter value to insert: ";
      cin >> value;
      insert(&l, value);
      break;
    }
    case 2: {
      int pos, value;
      cout << "Enter position and value to insert: ";
      cin >> pos >> value;
      insert(&l, pos, value);
      break;
    }
    case 3: {
      int pos;
      cout << "Enter position to delete: ";
      cin >> pos;
      del(&l, pos);
      break;
    }
    case 4: {
      int value;
      cout << "Enter value to search: ";
      cin >> value;
      int pos = search(l, value);
      if (pos != -1) {
        cout << "Value found at position: " << pos << endl;
      } else {
        cout << "Value not found in the list.\n";
      }
      break;
    }
    case 5: {
      cout << "List contents: ";
      print(l);
      break;
    }
    case 6: {
      cout << "Exiting program.\n";
      break;
    }
    default: {
      cout << "Invalid choice. Please try again.\n";
      break;
    }
    }
  } while (choice != 6);

  return 0;
}
