#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int d;
    struct node *next;
}node;

typedef node* clist;

void init(clist *l){
    *l = NULL;
    return;
}

void insert_end(clist *l, int d){
    node *nn = (node *) malloc(sizeof(node));
    if(nn){
        nn->d = d;
        nn->next = NULL;
    }

    if(*l == NULL){
        *l = nn;
        nn->next = *l;
        return;
    }

    node *p = *l;
    nn->next = p;
    while(p->next != *l){
        p = p->next;
    }

    p->next = nn;
    nn->next=*l;
    return;
}

void delete_beg(clist *l) {
    if (*l == NULL) {
        return;
    }

    node *p = *l;
    *l = p->next;
    
    if (*l == p) {
        // Only one node in the list
        *l = NULL;
    } else {
        node *q = p;
        while (q->next != p) {
            q = q->next;
        }
        q->next = *l;
    }

    free(p);
    return;
}


void traverse(clist l){
    node *p = l;
    printf("[");
    if(!p){
        printf("]");
        return;
    }
    do{
        printf("%d ",p->d);
        p = p->next;
    }while(p != l);

    printf("]");
    return;
}

void main(){
    
    clist a;
    init(&a);
    insert_end(&a,1);
    insert_end(&a,2);
    delete_beg(&a);
    traverse(a);
}