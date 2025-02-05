#include <iostream>
using namespace std;

class Node {
public:
  int key;
  Node *left;
  Node *right;
  int height;

  Node(int val) {
    key = val;
    left = right = nullptr;
    height = 1;
  }
};

class AVLTree {
private:
  int getHeight(Node *node) { return node ? node->height : 0; }

  int getBalanceFactor(Node *node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
  }

  void updateHeight(Node *node) {
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
  }
};
