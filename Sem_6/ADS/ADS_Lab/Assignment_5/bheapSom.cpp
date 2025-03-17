#include <iostream>
#include <climits>
#include <unordered_map>
using namespace std;

// Binomial Heap Node
struct BinomialNode {
    int key;
    int degree;
    BinomialNode* parent;
    BinomialNode* child;
    BinomialNode* sibling;

    BinomialNode(int k) : key(k), degree(0), parent(nullptr), child(nullptr), sibling(nullptr) {}
};

// Binomial Heap class
class BinomialHeap {
private:
    BinomialNode* head;
    unordered_map<int, BinomialNode*> nodeMap; // Maps keys to their nodes for quick access

    // Merge two binomial trees
    BinomialNode* mergeTrees(BinomialNode* b1, BinomialNode* b2) {
        if (b1->key > b2->key) swap(b1, b2);
        b2->parent = b1;
        b2->sibling = b1->child;
        b1->child = b2;
        b1->degree++;
        return b1;
    }

    // Merge two binomial heaps
    BinomialNode* mergeHeaps(BinomialNode* h1, BinomialNode* h2) {
        if (!h1) return h2;
        if (!h2) return h1;
        
        BinomialNode* head = nullptr, *tail = nullptr, *h1next = h1, *h2next = h2;
        
        while (h1next && h2next) {
            BinomialNode* minNode = nullptr;
            if (h1next->degree <= h2next->degree) {
                minNode = h1next;
                h1next = h1next->sibling;
            } else {
                minNode = h2next;
                h2next = h2next->sibling;
            }

            if (!head) {
                head = tail = minNode;
            } else {
                tail->sibling = minNode;
                tail = minNode;
            }
        }

        tail->sibling = h1next ? h1next : h2next;
        return head;
    }

    // Adjust heap after merging
    BinomialNode* adjustHeap(BinomialNode* head) {
        if (!head) return nullptr;

        BinomialNode* prev = nullptr, *curr = head, *next = head->sibling;
        while (next) {
            if ((curr->degree != next->degree) || 
                (next->sibling && next->sibling->degree == curr->degree)) {
                prev = curr;
                curr = next;
            } else {
                if (curr->key <= next->key) {
                    curr->sibling = next->sibling;
                    mergeTrees(curr, next);
                } else {
                    if (!prev) head = next;
                    else prev->sibling = next;
                    mergeTrees(next, curr);
                    curr = next;
                }
            }
            next = curr->sibling;
        }
        return head;
    }

    // Extract minimum node
    BinomialNode* extractMinNode() {
        if (!head) return nullptr;

        BinomialNode *minNode = head, *minPrev = nullptr;
        BinomialNode *curr = head, *prev = nullptr;

        int minKey = head->key;

        while (curr->sibling) {
            if (curr->sibling->key < minKey) {
                minKey = curr->sibling->key;
                minPrev = curr;
                minNode = curr->sibling;
            }
            curr = curr->sibling;
        }

        if (minPrev) minPrev->sibling = minNode->sibling;
        else head = minNode->sibling;

        nodeMap.erase(minNode->key); // Remove from tracking map

        BinomialNode* child = minNode->child;
        BinomialNode* reversedChild = nullptr;
        while (child) {
            BinomialNode* next = child->sibling;
            child->sibling = reversedChild;
            reversedChild = child;
            child = next;
        }

        head = mergeHeaps(head, reversedChild);
        head = adjustHeap(head);

        return minNode;
    }

public:
    BinomialHeap() : head(nullptr) {}

    // Insert a key
    void insert(int key) {
        BinomialHeap tempHeap;
        BinomialNode* newNode = new BinomialNode(key);
        tempHeap.head = newNode;
        nodeMap[key] = newNode;
        head = mergeHeaps(head, tempHeap.head);
        head = adjustHeap(head);
    }

    // Find minimum key
    int findMin() {
        if (!head) return -1;
        int minKey = INT_MAX;
        BinomialNode* curr = head;
        while (curr) {
            minKey = min(minKey, curr->key);
            curr = curr->sibling;
        }
        return minKey;
    }

    // Unite with another heap
    void unite(BinomialHeap& other) {
        head = mergeHeaps(head, other.head);
        head = adjustHeap(head);
    }

    // Extract minimum key
    int extractMin() {
        BinomialNode* minNode = extractMinNode();
        if (!minNode) return -1;
        int minKey = minNode->key;
        delete minNode;
        return minKey;
    }

    // Decrease a key
    void decreaseKey(int oldKey, int newKey) {
        if (nodeMap.find(oldKey) == nodeMap.end() || newKey > oldKey) {
            cout << "Invalid key operation.\n";
            return;
        }
        BinomialNode* node = nodeMap[oldKey];
        nodeMap.erase(oldKey);
        node->key = newKey;
        nodeMap[newKey] = node;

        while (node->parent && node->key < node->parent->key) {
            swap(node->key, node->parent->key);
            swap(nodeMap[node->key], nodeMap[node->parent->key]);
            node = node->parent;
        }
    }

    // Delete a key
    void deleteKey(int key) {
        decreaseKey(key, INT_MIN);
        extractMin();
    }
};

int main() {
    BinomialHeap heap;
    int choice, key, newKey;
    
    while (true) {
        cout << "\n1. Insert Key\n2. Find Minimum\n3. Extract Minimum\n";
        cout << "4. Unite with Another Heap\n5. Decrease Key\n6. Delete Key\n7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter key to insert: ";
                cin >> key;
                heap.insert(key);
                break;
            case 2:
                cout << "Minimum key: " << heap.findMin() << endl;
                break;
            case 3:
                cout << "Extracted minimum key: " << heap.extractMin() << endl;
                break;
            case 4: {
                BinomialHeap otherHeap;
                cout << "Enter number of elements in second heap: ";
                int n, val;
                cin >> n;
                for (int i = 0; i < n; i++) {
                    cout << "Enter key: ";
                    cin >> val;
                    otherHeap.insert(val);
                }
                heap.unite(otherHeap);
                cout << "Heaps united.\n";
                break;
            }
            case 5:
                cout << "Enter key to decrease: ";
                cin >> key;
                cout << "Enter new key value: ";
                cin >> newKey;
                heap.decreaseKey(key, newKey);
                break;
            case 6:
                cout << "Enter key to delete: ";
                cin >> key;
                heap.deleteKey(key);
                break;
            case 7:
                return 0;
            default:
                cout << "Invalid choice!\n";
        }
    }
    return 0;
}
