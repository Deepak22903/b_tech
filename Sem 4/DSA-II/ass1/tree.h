struct Node {
    int MIS;
    char Name[50];
    struct Node* left;
    struct Node* right;
};

struct Node* initBST();
struct Node* insertNode(struct Node* root, int MIS, const char* Name);
int countNodes(struct Node* root);
struct Node* removeNode(struct Node* root, int MIS);
struct Node* search(struct Node* root, int MIS);
void inorder(struct Node* root);
void preorder(struct Node* root);
void postorder(struct Node* root);

