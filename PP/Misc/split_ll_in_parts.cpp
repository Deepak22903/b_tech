#include <vector>
using namespace std;
struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
  int length(ListNode *head) {
    int len = 0;
    while (head) {
      head = head->next;
      len++;
    }
    return len;
  }

  vector<ListNode *> splitListToParts(ListNode *head, int k) {
    vector<ListNode *> res;
    ListNode *curr = head;
    ListNode *prev = nullptr;
    int len = length(curr);
    int q = len / k;
    int r = len % k;
    vector<int> arr(k, q);
    for (int i = 0; i < r; i++) {
      arr[i] += 1;
    }
    for (int i = 0; i < arr.size(); i++) {
      res.push_back(curr);
      if (!(i == 0) && !(prev == nullptr))
        prev->next = nullptr;
      for (int j = 0; j < arr[i]; j++) {
        prev = curr;
        curr = curr->next;
      }
    }
    return res;
  }
};
