#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node *left, *right;
} node;

typedef node *tree;

void init(tree *root) {
    *root = NULL;
    return;
}

node *create_node(int data) {
    node *nn = (node *)malloc(sizeof(node));
    if (nn) {
        nn->data = data;
        nn->left = nn->right = NULL;
    }
    return nn;
}

void inorder(tree root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void preorder(tree root) {
    if (root == NULL) {
        return;
    }
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void postorder(tree root) {
    if (root == NULL) {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

void insert(tree *root, int data) {
    node *p, *q;
    p = *root;
    q = NULL;
    while (p) {
        q = p;
        if (data == p->data) {
            return;
        }
        if (data < p->data) {
            p = p->left;
        } else {
            p = p->right;
        }
    }

    node *new_node = create_node(data);

    if (q == NULL) {
        *root = new_node;
    } else if (data < q->data) {
        q->left = new_node;
    } else {
        q->right = new_node;
    }
    return;
}

int search(tree *root, int key) {
    node *p = *root;
    while (p) {
        if (key == p->data) {
            printf("\nData is Present😁!\n");
            return 1;
        } else if (key < p->data) {
            p = p->left;
        } else {
            p = p->right;
        }
    }
    printf("\nData not Found 😔\n");
    return 0;
}

void delete (tree *root, int key) {
    node *parent, *current;
    current = *root;
    parent = NULL;

    while (current != NULL && key != current->data) {
        parent = current;
        if (key < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == NULL) {
        printf("Node to be deleted not found!😔😔");
        return;
    }

    if (current->left == NULL && current->right == NULL) {
        if (*root == current) {
            *root == NULL;
        } else if (parent->left == current) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
        free(current);
    } else if (current->left == NULL || current->right == NULL) {
        node *child = (current->left != NULL) ? current->left : current->right;
        if (*root == current) {
            *root = child;
        } else if (parent->left == current) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        free(current);
    } else {
        node *successor = current->right;
        parent = current;
        while (successor->left != NULL) {
            parent = successor;
            successor = successor->left;
        }

        current->data = successor->data;

        if (parent->left == successor) {
            parent->left = successor->right;
        } else {
            parent->left = successor->right;
        }
        free(successor);
    }
}

int count(tree root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + count(root->left) + count(root->right);
}

int getHeight(node *root) {
    if (root == NULL)
        return 0;
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

bool isComplete(node *root, int index, int totalNodes) {
    if (root == NULL)
        return true;
    if (index >= totalNodes)
        return false;
    return isComplete(root->left, 2 * index + 1, totalNodes) && isComplete(root->right, 2 * index + 2, totalNodes);
}

int countNodes(node *root) {
    if (root == NULL)
        return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int height(tree root) {
    if (root == NULL) {
        return -1;
    }
    int left_height = height(root->left);
    int right_height = height(root->right);

    return 1 + ((left_height > right_height) ? left_height : right_height);
}

void print_level(tree root, int level) {
    if (root == NULL) {
        return;
    }
    if (level == 1) {
        printf("%d ", root->data);
    } else if (level > 1) {
        print_level(root->left, level - 1);
        print_level(root->right, level - 1);
    }
}

void level_Order(tree root) {
    int h = height(root);
    for (int i = 1; i <= h + 1; i++) {
        print_level(root, i);
    }
}

int main() {
    tree t1;
    init(&t1);

    // Values to insert
    int values[] = {25, 20, 36, 10, 22, 30, 40, 5, 12, 28, 38, 48, 1, 8, 15, 45, 50};
    int num_values = sizeof(values) / sizeof(values[0]);

    // Inserting values into the tree
    for (int i = 0; i < num_values; i++) {
        insert(&t1, values[i]);
    }

    printf("Postorder traversal: ");
    postorder(t1);
    printf("\n");

    printf("Preorder traversal: ");
    preorder(t1);
    printf("\n");

    int totalNodes = countNodes(t1);

    if (isComplete(t1, 0, totalNodes))
        printf("The binary tree is complete.\n");
    else
        printf("The binary tree is not complete.\n");

    return 0;
}

