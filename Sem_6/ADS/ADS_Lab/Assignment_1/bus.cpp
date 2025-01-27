#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Queue {
private:
  int front, rear;
  vector<string> namearr;

public:
  Queue() : front(-1), rear(-1) {}

  void push(const string &name) {
    if (front == -1) {
      front = 0;
    }
    rear++;
    if (rear < namearr.size()) {
      namearr[rear] = name;
    } else {
      namearr.push_back(name);
    }
    cout << name << " added to the queue.\n";
  }

  void pop() {
    if (empty()) {
      cout << "Queue Underflow\n";
      return;
    }
    front++;
    if (front > rear) {
      front = rear = -1;
    }
  }

  string top() const {
    if (empty()) {
      return "Queue is empty!";
    }
    return namearr[front];
  }

  bool empty() const { return front == -1 || front > rear; }

  void remove(const string &name) {
    bool found = false;
    vector<string> newQueue;
    for (int i = front; i <= rear; ++i) {
      if (namearr[i] == name && !found) {
        found = true;
      } else {
        newQueue.push_back(namearr[i]);
      }
    }
    if (found) {
      cout << "Processed booking for: " << name << "\n";
    } else {
      cout << "Booking for " << name << " not found.\n";
    }

    namearr = newQueue;
    front = newQueue.empty() ? -1 : 0;
    rear = newQueue.size() - 1;
  }

  void display() const {
    if (empty()) {
      cout << "Queue is empty!\n";
      return;
    }
    cout << "Current Queue: ";
    for (int i = front; i <= rear; ++i) {
      cout << namearr[i] << " ";
    }
    cout << "\n";
  }
};

int main() {
  Queue q;
  int choice;

  cout << "Welcome to Bus Booking!\n\n";

  while (true) {
    cout << "\n1. Add Customer\n2. Process Booking\n3. View Queue\nEnter your "
            "Choice> ";
    cin >> choice;

    if (choice == 1) {
      cout << "Enter Name: ";
      string name;
      cin >> name;
      q.push(name);
    } else if (choice == 2) {
      cout << "Enter the name to remove: ";
      string name;
      cin >> name;
      q.remove(name);
    } else if (choice == 3) {
      q.display();
    } else {
      cout << "Invalid choice! Try again.\n";
    }
  }

  return 0;
}
