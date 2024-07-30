#include <stdio.h>
#include <stdlib.h>


typedef struct node{
    int data;
    struct node *left;
    struct node *right;
}node;

typedef node *tree;

void init(tree *t){
    *t = NULL;
    return;
}

node* create_node(int data){
    node *newnode = (node *) malloc(sizeof(node));
    newnode->data = data;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}


void insert(tree *t, int data){
    node *p = *t, *q;

    if(*t == NULL){
        *t = create_node(data);
        return;
    }

    while(p != NULL){
        q = p;
        
        if(data == p->data){
            return;
        }else if(data < p->data){
            p = p->left;
        }else{
            p = p->right;
        }
    }

    if(data < q->data){
        q->left = create_node(data);
    }else{
        q->right = create_node(data);
    }
    return;
}

int count(tree t){

    if(t == NULL)
    return 0;
    return 1 + count(t->left) + count(t->right);
}

void inorder(tree t){
    if(t == NULL)
    return;
    inorder(t->left);
    printf(" %d",t->data);
    inorder(t->right);
}

void preorder(tree t){
    if(t == NULL){
        return;
    }
    printf(" %d",t->data);
    preorder(t->left);
    preorder(t->right);
}

void postorder(tree t){
    if(t == NULL)
    return;
    postorder(t->left);
    postorder(t->right);
    printf(" %d", t->data);
}


void delete(tree *t, int data){
    node *p = *t, *q;

    while(p != NULL && p->data != data){
        q = p;
        if(data < p->data){
            p = p->left;
        }else{
            p = p->right;
        }
    }

    if(p == NULL){
        return;
    }

    //Condition 1

    if(p->left == NULL && p->right == NULL){
        if(*t == p){
            *t = NULL;
            free(p);
            return;   
        }

        if(q->left == p){
                q->left = NULL;
            }else if(q->right == p){
                q->right = NULL;
            }

        free(p);
        return;

    }

    //Condition 2

    if(p->left == NULL || p->right == NULL){
        node *c = (p->left == NULL) ? p->right : p->left;

        if(*t == p){
            *t = c;
            free(p);
            return;
        }

        if(p->left == c){
            q->left = c;
        }else if(p->right == c){
            q->right = c;
        }

        free(p);
        return;
    }


    //Condition 3

    if(p->left != NULL && p->right != NULL){
        node *s = p->right;

        while(s->left != NULL){
            q = s;
            s = s->left;
        }

        p->data = q->data;

        if(q->left == s){
            q->left = s->right;
        }else if(q->right == s){
            q->right = s->right;
        }

        free(s);
        return;
    }
}

int search(tree *t, int data){
    node *p = *t;

    while(p != NULL){
        if(data == p->data){
            printf("\nData Found");
            return 1;
        }else if(data < p->data){
            p = p->left;
        }else{
            p = p->right;
        }
    }
    printf("\nData not Found");
    return 0;
}


int main(){
    tree t;
    init(&t);
    insert(&t,1);
    insert(&t,2);
    insert(&t,3);
    delete(&t,3);
    insert(&t,4);
    insert(&t,5);
    insert(&t,6);
    delete(&t,1);
    search(&t,2);
    inorder(t);
    printf("\nCount : %d",count(t));
    return 0;
}