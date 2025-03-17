#pragma once

#include <climits>
#include <iostream>
#include <string>

using namespace std;

struct truck {
  truck *parent;
  truck *sibling;
  truck *child;
  int distance;
  int urgency; /*
  0 : mostUrgent
  1 : mediumUrgent
  2 : notUrgent
  */
  int truckId;
  int degree;
  truck(int truckId, int distance, int urgency)
      : truckId(truckId), distance(distance), urgency(urgency), degree(0),
        parent(nullptr), sibling(nullptr), child(nullptr) {};
};

struct hub {
  truck *truckHub;
  hub *next;
  hub(truck *hub) : truckHub(hub), next(nullptr) {};
};

class LogisticCompany {
private:
  truck *mergeHeaps(truck *h1, truck *h2);
  void linkNodes(truck *curr, truck *next);
  truck *unionHeap(truck *h1, truck *h2);
  void display(truck *head);
  truck *reverseList(truck *head);
  truck *findMinPrevNode();
  truck *findNodeHelper(truck *root, int targetKey);
  truck *findNode(int targetKey);

public:
  truck *head;
  LogisticCompany() : head(nullptr) {};
  bool empty();
  void insertTruck(int truckId, int distance, int urgency);
  void deleteTruck(int truckId);
  int getMinPriorityTruck();
  void sendMinPriorityTruck();
  void display();
  void decreaseKey(int targetKey, int newKey);
  void extractMin();
  void deleteKey(int targetKey);
};
