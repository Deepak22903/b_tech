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
private:
  Node *head;
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
    Node *temp = head;
    int min = INT_MAX;
    int lastmin{};
    while (temp) {
      if (temp->key < min) {
        lastmin = temp->key;
        min = temp->key;
      }
      temp = temp->sibling;
    }
    if (!lastmin)
      temp = findNode(min);
    temp = findNode(lastmin);
    return temp;
  }

public:
  bHeap() : head(nullptr) {};
  Node *insert(int key) {
    Node *nn = new Node(key);
    head = unionHeap(head, nn);
    return head;
  }
  void displayTree(Node *root, int depth = 0) {
    if (!root)
      return;

    // Print indentation for tree structure
    for (int i = 0; i < depth; i++) {
      cout << "  ";
    }

    // Print current node key
    cout << root->key << endl;

    // Print child nodes (with increased indentation)
    displayTree(root->child, depth + 1);

    // Print sibling nodes at the same level
    displayTree(root->sibling, depth);
  }

  void display() {
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
    while (targetNode->parent) {
      if (targetNode->parent->key > targetNode->key) {
        swap(targetNode->key, targetNode->parent->key);
      }
      targetNode = targetNode->parent;
    }
  }

  int findMin() { return findMinPrevNode()->sibling->key; }

  void extractMin() {
    Node *minPrev = findMinPrevNode();
    if (!minPrev)
      cerr << "Extraction Failed" << endl;
    return;
    Node *min = minPrev->sibling;
    if (min)
      minPrev->sibling = min->sibling;
    Node *childs = min->child;
    Node *nh = min->child;
    while (childs->sibling) {
      childs->parent = nullptr;
    }
    unionHeap(head, nh);
  }
};

int main(int argc, char *argv[]) {
  bHeap bHeap;
  bHeap.insert(10);
  bHeap.insert(20);
  bHeap.insert(30);
  bHeap.insert(40);
  bHeap.insert(50);
  // bHeap.decreaseKey(40, 5);
  bHeap.display();
  cout << "Min Key: " << bHeap.findMin() << endl;

  return 0;
}
