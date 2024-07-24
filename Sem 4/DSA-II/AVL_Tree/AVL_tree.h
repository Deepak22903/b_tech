#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    char name[50];
    struct node *left,*right,*parent;
    int bf;
} node;

typedef struct node* tree;

void init_AVL(tree *t);
node* creatNode(char *name);
int height(node *root);
void adjustBF(tree *t);
void adjustImbalance(tree *t, node *n);
void RR(tree *t, node *n);
void LL(tree *t, node *n);
void RL(tree *t, node *n);
void LR(tree *t, node *n);
void insertNode(tree *t, char *name);
void removeNode(tree *t, char *name);
void removeNodeRecursive(tree *t, char *name, node *parent);
void traverse(tree t);
void destroyTree(tree *t);