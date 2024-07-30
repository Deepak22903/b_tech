#include "AVL_tree.h"

void init_AVL(tree *t){
    *t = NULL;
}

node* creatNode(char *name){
    node *p = (node *) malloc(sizeof(node));
    if(p){
        strcpy(p->name, name);
        p->left = p->right = p->parent = NULL;
        p->bf = 0;
    }else printf("Node Creation Failed!");
    return p;
}

int height(node *root){
    node *p = root;
    if(!p){
        return 0;
    }

    int left_height;
    left_height = height(p->left);
    int right_height;
    right_height = height(p->right);

    return 1 + (left_height > right_height ? left_height : right_height);
}

void adjustBF(tree *t){
    node *p = *t;

    while(p){
        p->bf = height(p->left) - height(p->right);
        p = p->parent;
    }
}

void adjustImbalance(tree *t, node *n){
    while(n){
        n->bf = height(n->left) - height(n->right);
        if(n->bf < -1){
            if(n->right->bf <= 0){
                RR(t,n);
            }else{
                LR(t,n);
            }
        }else if(n->bf > 1){
            if(n->left->bf >= 0){
                LL(t,n);
            }else{
                RL(t,n);
            }
        }
        n = n->parent;
    }
}

void RR(tree *t, node *n){
    node *temp = n->right;
    n->right = temp->left;
    if(n->right) n->right->parent = n;
    temp->left = n;
    temp->parent = n->parent;
    n->parent = temp;
    if(temp->parent){
        if(temp->parent->left == n){
        temp->parent->left = temp;
    }else{
        temp->parent->right = temp;
    }
    }else *t = temp;
    adjustBF(t);
}

void LL(tree *t, node *n){
    node *temp = n->left;
    n->left = temp->right;
    if(n->left) n->left->parent = n;
    temp->right = n;
    temp->parent = n->parent;
    n->parent = temp;
    if(temp->parent){
        if(temp->parent->left == n){
            temp->parent->left = temp;
        }else{
            temp->parent->right = temp;
        }
    }else *t = temp;

    adjustBF(t);
}

void RL(tree *t, node *n){
    RR(t,n->left);
    LL(t,n);
}

void LR(tree *t, node *n){
    LL(t,n->right);
    RR(t,n);
}

void insertNode(tree *t, char *name){
    node *nn = creatNode(name);

    node *p = *t;
    node *parent = NULL;

    if(!p){
        *t = nn;
        adjustBF(t);
        return;
    }

    while(p){
        parent = p;

        if(strcmp(p->name, name) == 0){
            free(nn);
            return;
        }else if(strcmp(p->name, name) > 0){
            p = p->left;
        }else{
            p = p->right;
        }
    }

    if(strcmp(name, parent->name) < 0){
        parent->left = nn;
    }else{
        parent->right = nn;
    }

    nn->parent = parent;

    adjustBF(t);
    adjustImbalance(t, nn->parent);
}

void removeNode(tree *t, char *name){
    removeNodeRecursive(t, name, NULL);
}

void removeNodeRecursive(tree *t, char *name, node *parent){
    if(*t == NULL){
        return;
    }

    node *p = *t;

    if(strcmp(p->name, name) > 0){
        removeNodeRecursive(&(p->left), name, p);
    }else if(strcmp(p->name, name) < 0){
        removeNodeRecursive(&(p->right), name, p);
    }else{
        if(p->left == NULL && p->right == NULL){
            if(parent){
                if(parent->left == p){
                    parent->left = NULL;
                }else{
                    parent->right = NULL;
                }
            }else{
                *t = NULL;
            }
            free(p);
        }
        else if(p->left == NULL || p->right == NULL){
            node *child = (p->left != NULL) ? p->left : p->right;
            if(parent){
                if(parent->left == p){
                    parent->left = child;
                }else{
                    parent->right = child;
                }
            }else{
                *t = child;
            }
            child->parent = parent;
            free(p);
        }
        else{
            node *succ = p->right;
            while(succ->left){
                succ = succ->left;
            }
            strcpy(p->name, succ->name);
            removeNodeRecursive(&(p->right), succ->name, p);
        }
        adjustBF(t);
        adjustImbalance(t, parent);
    }
}

void traverse(tree t){
    node *p = t;
    if(p == NULL){
        return;
    }
    traverse(p->left);
    printf("%s ",p->name);
    traverse(p->right);
}

void destroyTree(tree *t){
    if(*t == NULL){
        return;
    }

    destroyTree(&((*t)->left));
    destroyTree(&((*t)->right));

    free(*t);
    *t = NULL;
}