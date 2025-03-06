#include <cstdlib> // For rand()
#include <iostream>
using namespace std;

struct Task {
  int id, priority;
  Task *left, *right;
  Task(int id, int priority)
      : id(id), priority(priority), left(nullptr), right(nullptr) {}
};

class TreapTaskScheduler {
public:
  Task *root;

  TreapTaskScheduler() : root(nullptr) {}

  // Right rotation
  Task *rotateRight(Task *y) {
    Task *x = y->left;
    y->left = x->right;
    x->right = y;
    return x;
  }

  // Left rotation
  Task *rotateLeft(Task *x) {
    Task *y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
  }

  // Insert a new task
  Task *insert(Task *root, int id, int priority) {
    if (!root)
      return new Task(id, priority);

    if (id < root->id) {
      root->left = insert(root->left, id, priority);
      if (root->left->priority > root->priority)
        root = rotateRight(root);
    } else {
      root->right = insert(root->right, id, priority);
      if (root->right->priority > root->priority)
        root = rotateLeft(root);
    }
    return root;
  }

  void insert(int id, int priority) { root = insert(root, id, priority); }

  // Delete a task by id
  Task *deleteTask(Task *root, int id) {
    if (!root)
      return root;

    if (id < root->id) {
      root->left = deleteTask(root->left, id);
    } else if (id > root->id) {
      root->right = deleteTask(root->right, id);
    } else {
      if (!root->left)
        return root->right;
      if (!root->right)
        return root->left;

      if (root->left->priority > root->right->priority) {
        root = rotateRight(root);
        root->right = deleteTask(root->right, id);
      } else {
        root = rotateLeft(root);
        root->left = deleteTask(root->left, id);
      }
    }
    return root;
  }

  void deleteTask(int id) { root = deleteTask(root, id); }

  // Find the highest-priority task
  Task *getHighestPriorityTask(Task *root) {
    if (!root)
      return nullptr;

    Task *maxTask = root;
    if (root->left) {
      Task *leftMax = getHighestPriorityTask(root->left);
      if (leftMax && leftMax->priority > maxTask->priority)
        maxTask = leftMax;
    }
    if (root->right) {
      Task *rightMax = getHighestPriorityTask(root->right);
      if (rightMax && rightMax->priority > maxTask->priority)
        maxTask = rightMax;
    }
    return maxTask;
  }

  void getHighestPriorityTask() {
    Task *task = getHighestPriorityTask(root);
    if (task)
      cout << "Highest-priority task: ID = " << task->id
           << ", Priority = " << task->priority << endl;
    else
      cout << "No tasks available." << endl;
  }

  // In-order traversal
  void inorder(Task *root) {
    if (!root)
      return;
    inorder(root->left);
    cout << "(ID: " << root->id << ", Priority: " << root->priority << ") ";
    inorder(root->right);
  }

  void inorder() {
    inorder(root);
    cout << endl;
  }
};

int main() {
  TreapTaskScheduler scheduler;
  int choice;

  do {
    cout << "\nTask Scheduler Menu:\n";
    cout << "1. Insert Task\n";
    cout << "2. Delete Task\n";
    cout << "3. Get Highest Priority Task\n";
    cout << "4. Display Tasks (In-Order)\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1: {
      int id, priority;
      cout << "Enter Task ID: ";
      cin >> id;
      cout << "Enter Task Priority: ";
      cin >> priority;
      scheduler.insert(id, priority);
      break;
    }
    case 2: {
      int id;
      cout << "Enter Task ID to delete: ";
      cin >> id;
      scheduler.deleteTask(id);
      break;
    }
    case 3:
      scheduler.getHighestPriorityTask();
      break;
    case 4:
      scheduler.inorder();
      break;
    case 5:
      cout << "Exiting...\n";
      break;
    default:
      cout << "Invalid choice! Try again.\n";
    }
  } while (choice != 5);

  return 0;
}
