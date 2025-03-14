#include <algorithm>
#include <climits>
#include <iostream>
using namespace std;

struct Node {
  Node *parent;
  Node *child;
  Node *sibling;
  int key;
  int degree;
  Node(int key)
      : key(key), degree(0), parent(nullptr), child(nullptr),
        sibling(nullptr) {};
};

class bHeap {
public:
  Node *head;
  bool empty() {
    if (!head)
      return true;
    return false;
  }
  Node *mergeHeap(Node *h1, Node *h2) {
    if (!h1)
      return h2;
    if (!h2)
      return h1;

    Node *head = nullptr;
    Node *tail = nullptr;

    if (h1->degree <= h2->degree) {
      head = h1;
      h1 = h1->sibling;
    } else {
      head = h2;
      h2 = h2->sibling;
    }
    tail = head;

    while (h1 && h2) {
      if (h1->degree <= h2->degree) {
        tail->sibling = h1;
        h1 = h1->sibling;
      } else {
        tail->sibling = h2;
        h2 = h2->sibling;
      }
      tail = tail->sibling;
    }

    if (h1)
      tail->sibling = h1;
    if (h2)
      tail->sibling = h2;

    return head;
  }
  void linkNodes(Node *curr, Node *next) {
    next->sibling = curr->child;
    next->parent = curr;
    curr->child = next;
    curr->degree++;
  }

  Node *unionHeap(Node *h1, Node *h2) {
    Node *nh = mergeHeap(h1, h2);
    if (!nh)
      return nullptr;
    Node *prev = nullptr;
    Node *curr = nh;
    Node *next = nh->sibling;

    while (next) {
      if (curr->degree != next->degree ||
          (next->sibling && curr->degree == next->sibling->degree)) {
        prev = curr;
        curr = next;
      } else {
        if (curr->key <= next->key) {
          curr->sibling = next->sibling;
          linkNodes(curr, next);
        } else {
          if (!prev)
            nh = next;
          else
            prev->sibling = next;
          linkNodes(next, curr);
          curr = next;
        }
      }
      next = next->sibling;
    }
    return nh;
  }

  Node *findNodeHelper(Node *root, int targetKey) {
    if (!root)
      return nullptr;

    // Check the current node
    if (root->key == targetKey)
      return root;

    // Search in the child subtree
    Node *foundInChild = findNodeHelper(root->child, targetKey);
    if (foundInChild)
      return foundInChild;

    // Search in the sibling subtree
    return findNodeHelper(root->sibling, targetKey);
  }

  Node *findNode(int targetKey) { return findNodeHelper(head, targetKey); }

  Node *findMinPrevNode() {
    if (!head)
      return nullptr;
    if (!head->sibling)
      return nullptr; // No previous node if only one node

    Node *curr = head;
    Node *prev = nullptr;
    Node *minPrev = nullptr;
    Node *minNode = head;

    while (curr->sibling) {
      if (curr->sibling->key < minNode->key) {
        minPrev = curr;
        minNode = curr->sibling;
      }
      curr = curr->sibling;
    }

    return minPrev;
  }
  bHeap() : head(nullptr) {};
  Node *insert(int key) {
    Node *nn = new Node(key);
    head = unionHeap(head, nn);
    return head;
  }
  void displayTree(Node *h) {
    while (h) {
      cout << h->key << " ";
      displayTree(h->child);
      h = h->sibling;
    }
  }

  void display() {
    if (!head) {
      cout << "Binomial Heap empty!" << endl;
      return;
    }

    cout << "Binomial Heap Structure:" << endl;
    displayTree(head);
  }
  void decreaseKey(int targetKey, int newKey) {
    if (newKey > targetKey) {
      cerr << "New Key is Bigger!" << endl;
      return;
    }
    Node *targetNode = findNode(targetKey);
    if (!targetNode) {
      cerr << "targetKey not found!" << endl;
      return;
    }
    targetNode->key = newKey;
    while (targetNode->parent && targetNode->parent->key > targetNode->key) {
      swap(targetNode->key, targetNode->parent->key);
      targetNode = targetNode->parent;
    }
  }
  int findMin() {
    if (empty()) {
      cout << "empty!" << endl;
      return -1;
    }

    Node *curr = head;
    int minKey = head->key;

    while (curr) {
      if (curr->key < minKey) {
        minKey = curr->key;
      }
      curr = curr->sibling;
    }

    return minKey;
  }
  Node *reverseList(Node *head) {
    Node *prev = nullptr;
    Node *curr = head;
    while (curr) {
      curr->parent = nullptr; // Reset parent pointer
      Node *next = curr->sibling;
      curr->sibling = prev;
      prev = curr;
      curr = next;
    }
    return prev;
  }

  void extractMin() {
    if (!head) {
      cerr << "Binomial Heap is empty" << endl;
      return;
    }

    Node *minPrev = findMinPrevNode();
    Node *min = nullptr;

    if (!minPrev) { // Only one node in heap
      min = head;
      head = head->sibling;
    } else {
      min = minPrev->sibling;
      minPrev->sibling = min->sibling;
    }

    Node *childs = min->child;
    delete min;

    if (!childs) {
      cerr << "Min Extraction success!" << endl;
      return;
    }

    Node *nh = reverseList(childs);
    head = unionHeap(head, nh);
    cerr << "Min Extraction success!" << endl;
  }

  void deleteKey(int targetKey) {
    Node *targetNode = findNode(targetKey);
    if (!targetNode) {
      cerr << "Key not found in the heap!" << endl;
      return;
    }

    // Decrease key to negative infinity
    decreaseKey(targetKey, INT_MIN);

    // Extract the min (which removes the node)
    extractMin();
  }
};

int main() {
  bHeap heap;
  int choice, key, newKey;

  while (true) {
    cout << "\nBinomial Heap Operations:\n";
    cout << "1. Insert\n";
    cout << "2. Delete Key\n";
    cout << "3. Decrease Key\n";
    cout << "4. Extract Min\n";
    cout << "5. Find Min\n";
    cout << "6. Display Heap\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
      cout << "Enter key to insert: ";
      cin >> key;
      heap.insert(key);
      cout << "Inserted " << key << " into the heap.\n";
      break;
    case 2:
      cout << "Enter key to delete: ";
      cin >> key;
      heap.deleteKey(key);
      cout << "Deleted " << key << " from the heap.\n";
      break;
    case 3:
      cout << "Enter key to decrease: ";
      cin >> key;
      cout << "Enter new key value: ";
      cin >> newKey;
      heap.decreaseKey(key, newKey);
      cout << "Decreased " << key << " to " << newKey << ".\n";
      break;
    case 4:
      heap.extractMin();
      break;
    case 5:
      cout << "Minimum Key: " << heap.findMin() << endl;
      break;
    case 6:
      heap.display();
      break;
    case 7:
      cout << "Exiting...\n";
      return 0;
    default:
      cout << "Invalid choice! Try again.\n";
    }
  }

  return 0;
}
