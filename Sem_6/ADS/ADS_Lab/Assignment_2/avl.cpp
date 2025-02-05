#include <iostream>
using namespace std;

class Node {
public:
  int key;
  Node *left;
  Node *right;
  int height;

  Node(int value) {
    key = value;
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

  Node *rotateLL(Node *node) {
    Node *newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;

    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
  }

  Node *rotateRR(Node *node) {
    Node *newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;

    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
  }

  Node *rotateLR(Node *node) {
    node->left = rotateRR(node->left);
    return rotateLL(node);
  }

  Node *rotateRL(Node *node) {
    node->right = rotateLL(node->right);
    return rotateRR(node);
  }

  Node *rebalance(Node *node) {
    updateHeight(node);
    int balance = getBalanceFactor(node);

    if (balance > 1) {
      if (getBalanceFactor(node->left) >= 0)
        return rotateLL(node);
      else
        return rotateLR(node);
    } else if (balance < -1) {
      if (getBalanceFactor(node->right) <= 0)
        return rotateRR(node);
      else
        return rotateRL(node);
    }

    return node;
  }

  Node *insert(Node *node, int key) {
    if (!node)
      return new Node(key);

    if (key < node->key)
      node->left = insert(node->left, key);
    else if (key > node->key)
      node->right = insert(node->right, key);
    else
      return node;

    return rebalance(node);
  }

  Node *findMin(Node *node) {
    while (node->left)
      node = node->left;
    return node;
  }

  Node *deleteNode(Node *node, int key) {
    if (!node)
      return node;

    if (key < node->key)
      node->left = deleteNode(node->left, key);
    else if (key > node->key)
      node->right = deleteNode(node->right, key);
    else {

      if (!node->left || !node->right) {
        Node *temp = node->left ? node->left : node->right;
        delete node;
        return temp;
      }

      Node *temp = findMin(node->right);
      node->key = temp->key;
      node->right = deleteNode(node->right, temp->key);
    }

    return rebalance(node);
  }

  void inorder(Node *node) {
    if (!node)
      return;
    inorder(node->left);
    cout << node->key << " ";
    inorder(node->right);
  }

public:
  Node *root;

  AVLTree() { root = nullptr; }

  void insert(int key) { root = insert(root, key); }

  void deleteKey(int key) { root = deleteNode(root, key); }

  void inorderTraversal() {
    inorder(root);
    cout << endl;
  }

  int getTreeHeight() { return getHeight(root); }

  int getRootBalanceFactor() { return getBalanceFactor(root); }
};

int main() {
  AVLTree tree;
  int n, value, deleteKey, choice;

  cout << "Enter the number of elements: ";
  cin >> n;
  cout << "Enter the elements: ";
  for (int i = 0; i < n; i++) {
    cin >> value;
    tree.insert(value);
  }

  while (true) {
    cout << "\nMenu:\n";
    cout << "1. Insert\n";
    cout << "2. Delete\n";
    cout << "3. Print Inorder Traversal\n";
    cout << "4. Print Tree Height\n";
    cout << "5. Print Root Balance Factor\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
      cout << "Enter value to insert: ";
      cin >> value;
      tree.insert(value);
      break;
    case 2:
      cout << "Enter value to delete: ";
      cin >> deleteKey;
      tree.deleteKey(deleteKey);
      break;
    case 3:
      cout << "Inorder Traversal: ";
      tree.inorderTraversal();
      break;
    case 4:
      cout << "Tree Height: " << tree.getTreeHeight() << endl;
      break;
    case 5:
      cout << "Root Balance Factor: " << tree.getRootBalanceFactor() << endl;
      break;
    case 6:
      cout << "Exiting...\n";
      return 0;
    default:
      cout << "Invalid choice. Try again.\n";
    }
  }

  return 0;
}
