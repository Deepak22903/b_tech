#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *left, *right;
}node;

node* createNode(int data){
    node *newnode = (node *) malloc(sizeof(node));
    if(newnode){
        newnode->left = NULL;
        newnode->right = NULL;
        newnode->data = data;
    }
    return newnode;
}

void printTree(node *root){
    if(root == NULL){
        printf("Empty\n");
        return;
    }

    printf("value = %d\n",root->data);

    printTree(root->left);
    printTree(root->right);
    return;

}

int main(){
    node *n1 = createNode(1);
    node *n2 = createNode(2);
    node *n3 = createNode(3);
    node *n4 = createNode(4);
    node *n5 = createNode(5);

    n1->left = n2;
    n1->right = n3;
    n3->left = n4;
    n3->right = n5;

    printTree(n1);

    free(n1);
    free(n2);
    free(n3);
    free(n4);
    free(n5);

    return 0;
}