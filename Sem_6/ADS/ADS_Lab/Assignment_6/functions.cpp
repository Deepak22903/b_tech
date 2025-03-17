#include "header.h"

bool LogisticCompany::empty() {
  if (!head)
    return true;
  return false;
}

truck *LogisticCompany::mergeHeaps(truck *h1, truck *h2) {
  if (!h1)
    return h2;
  if (!h2)
    return h1;

  truck *hd = nullptr;
  truck *tail = nullptr;

  if (h1->degree <= h2->degree) {
    hd = h1;
    h1 = h1->sibling;
  } else {
    hd = h2;
    h2 = h2->sibling;
  }
  tail = hd;

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

  return hd;
}

void LogisticCompany::linkNodes(truck *curr, truck *next) {
  next->parent = curr;
  next->sibling = curr->child;
  curr->child = next;
  curr->degree++;
}

truck *LogisticCompany::unionHeap(truck *h1, truck *h2) {
  truck *nh = mergeHeaps(h1, h2);
  if (!nh)
    return nullptr;
  truck *prev = nullptr;
  truck *curr = nh;
  truck *next = nh->sibling;

  while (next) {
    if (curr->degree != next->degree ||
        (next->sibling && curr->degree == next->sibling->degree)) {
      prev = curr;
      curr = next;
    } else {
      if (curr->urgency <= next->urgency) {
        curr->sibling = next->sibling;
        linkNodes(curr, next);
      } else if (curr->urgency > next->urgency) {
        if (prev) {
          prev->sibling = curr;
        } else {
          nh = curr; // Update the new heap head if prev is nullptr
        }
        linkNodes(next, curr);
      } else {
        if (curr->distance <= next->distance) {
          curr->sibling = next->sibling;
          linkNodes(curr, next);
        } else if (curr->distance > next->distance) {
          if (!prev)
            nh = next;
          prev->sibling = curr;
          linkNodes(next, curr);
          curr = next;
        }
      }
    }
    next = curr->sibling;
  }

  return nh;
}

void LogisticCompany::insertTruck(int truckId, int distance, int urgency) {
  truck *nn = new truck(truckId, distance, urgency);
  head = unionHeap(head, nn);
}

void LogisticCompany::display(truck *head) {
  cout << head->truckId << endl;
  if (head->child)
    display(head->child);
  if (head->sibling)
    display(head->sibling);
}
void LogisticCompany::display() {
  truck *tmp = head;
  display(tmp);
}

// decreaseKey function
void LogisticCompany::decreaseKey(int targetKey, int newKey) {
  if (newKey > targetKey) {
    cerr << "New Key is Bigger!" << endl;
    return;
  }
  truck *targetNode = findNode(targetKey);
  if (!targetNode) {
    cerr << "targetKey not found!" << endl;
    return;
  }
  targetNode->urgency = newKey;
  while (targetNode->parent &&
         targetNode->parent->urgency > targetNode->urgency) {
    swap(targetNode->urgency, targetNode->parent->urgency);
    targetNode = targetNode->parent;
  }
}

// returns the minimum key
int LogisticCompany::getMinPriorityTruck() {
  if (empty()) {
    cout << "empty!" << endl;
    return -1;
  }

  truck *curr = head;
  int minKey = head->urgency;

  while (curr) {
    if (curr->urgency < minKey) {
      minKey = curr->urgency;
    }
    curr = curr->sibling;
  }

  return minKey;
}

// reverses the linked list
truck *LogisticCompany::reverseList(truck *head) {
  truck *prev = nullptr;
  truck *curr = head;
  while (curr) {
    curr->parent = nullptr; // Reset parent pointer
    truck *next = curr->sibling;
    curr->sibling = prev;
    prev = curr;
    curr = next;
  }
  return prev;
}

// extractMin function
void LogisticCompany::extractMin() {
  if (!head) {
    cerr << "Binomial Heap is empty" << endl;
    return;
  }

  truck *minPrev = findMinPrevNode();
  truck *min = nullptr;

  if (!minPrev) { // Only one node in heap
    min = head;
    head = head->sibling;
  } else {
    min = minPrev->sibling;
    minPrev->sibling = min->sibling;
  }

  truck *childs = min->child;
  delete min;

  if (!childs) {
    cerr << "Min Extraction success!" << endl;
    return;
  }

  truck *nh = reverseList(childs);
  head = unionHeap(head, nh);
  cerr << "Min Extraction success!" << endl;
}

// removes the node with the specified key
void LogisticCompany::deleteKey(int targetKey) {
  truck *targetNode = findNode(targetKey);
  if (!targetNode) {
    cerr << "Key not found in the heap!" << endl;
    return;
  }

  // Decrease key to negative infinity
  decreaseKey(targetKey, INT_MIN);

  // Extract the min (which removes the node)
  extractMin();
}

truck *LogisticCompany::findNodeHelper(truck *root, int targetKey) {
  if (!root)
    return nullptr;

  // Check the current node
  if (root->urgency == targetKey)
    return root;

  // Search in the child subtree
  truck *foundInChild = findNodeHelper(root->child, targetKey);
  if (foundInChild)
    return foundInChild;

  // Search in the sibling subtree
  return findNodeHelper(root->sibling, targetKey);
}

truck *LogisticCompany::findNode(int targetKey) {
  return findNodeHelper(head, targetKey);
}

// returns previous node of the smallest node
truck *LogisticCompany::findMinPrevNode() {
  if (!head)
    return nullptr;
  if (!head->sibling)
    return nullptr; // No previous node if only one node

  truck *curr = head;
  truck *prev = nullptr;
  truck *minPrev = nullptr;
  truck *minNode = head;

  while (curr->sibling) {
    if (curr->sibling->urgency < minNode->urgency) {
      minPrev = curr;
      minNode = curr->sibling;
    }
    curr = curr->sibling;
  }

  return minPrev;
}
