struct node {
    int MIS;
    char Name[50];
    struct node* left;
    struct node* right;
};

struct node* initBST();
struct node* insertNode(struct node* root, int MIS, char* Name);
int countNodes(struct node* root);
struct node* removeNode(struct node* root, int MIS);
struct node* search(struct node* root, int MIS);
void inorder(struct node* root);
void preorder(struct node* root);
void postorder(struct node* root);

