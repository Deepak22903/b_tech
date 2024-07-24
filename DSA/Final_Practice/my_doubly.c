#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *next, *prev;
} node;

typedef struct list{
    struct node *front, *rear;
}list;

void init(list *l){
    l->front= NULL;
    l->rear= NULL;
}

int isNULL(list l){
    if(l.front == NULL){
        return 1;
    }
    return 0;
}

void insert_right(list *l, int d){
    node *newnode = (node *) malloc(sizeof(node));
    if(newnode){
        newnode->data=d;
        newnode->next= NULL;
        newnode->prev= NULL;
    }else return;

    if(!isNULL(*l)){
        node *temp = l->front;
        while(temp->next != NULL) temp = temp->next;
        temp->next = newnode;
        newnode->prev = temp;
        l->rear = newnode;
    } else{
        l->front = newnode;
        l->rear = newnode;
    }
}

void print_LR(list l){
    node *p = l.front;
    printf("[");
    if(!p){
        printf("]");
        return;
    }

    do{
        printf("%d ",p->data);
        p = p->next;
    }while(p);
    
    printf("]");
}

void print_RL(list l){
    node *p = l.rear;
    printf("[");
    if(!p){
        printf("]");
        return;
    }

    do{
        printf("%d ",p->data);
        p = p->prev;
    }while(p);

    printf("]");
}

int length(list l){
    node *p = l.front;
    int count=0;

    while(p){
        p= p->next;
        count++;
    }
    return count;
}

void reverse_list(list *l){
    node *p1,*p2;
    p1 = l->front;
    p2 = l->rear;

    while(p1 != p2 && p2 != p1->prev){
        int temp = p1->data;
        p1->data = p2->data;
        p2->data = temp;
        p1 = p1->next;
        p2 = p2->prev;
    }
    return;
}

void insert_sorted(list *l, int d){
    node *newnode = (node *) malloc(sizeof(node));
    if(newnode){
        newnode->data = d;
        newnode->next = NULL;
        newnode->prev = NULL;
    }

    if(isNULL(*l)){
        l->front= newnode;
        l->rear = newnode;
        return;
    }

    node *p = l->front;
    while(p->next != NULL && p->data < d){
        p = p->next;
    }

    if(p == l->front){
        l->front = newnode;
        newnode->next = p;
        p->prev = newnode;
        return;
    }

    if(p == l->rear && p->data < d){
        l->rear = newnode;
        p->next= newnode;
        newnode->prev = p;
        return;
    }
    p=p->prev;
    newnode->next = p->next;
    p->next = newnode;
    newnode->prev = p;
    return;
}

void remove_from_list(list *l, int d) {
    if (isNULL(*l)) {
        return;
    }

    node *p = l->front;

    while (p) {
        if (p->data == d) {
            if (p == l->front && p == l->rear) {
                // Only one node in the list
                l->front = NULL;
                l->rear = NULL;
            } else if (p == l->front) {
                // Removing the front node
                l->front = p->next;
                l->front->prev = NULL;
            } else if (p == l->rear) {
                // Removing the rear node
                l->rear = p->prev;
                l->rear->next = NULL;
            } else {
                // Removing a node in the middle
                p->prev->next = p->next;
                p->next->prev = p->prev;
            }

            free(p); // Free the memory of the removed node
            return;
        }

        p = p->next;

    }
}

void free_list(list *l){
    node *p = l->front;
    node *q;

    while(p){
        q = p;
        p = p->next;
        free(q);
    }
    l->front= NULL;
    l->rear = NULL;
}



int main(){
    list a;
    init(&a);
    insert_right(&a,1);
    insert_right(&a,2);
    insert_right(&a,3);
    insert_sorted(&a,2);
    remove_from_list(&a,3);
    print_LR(a);
    printf("\n");
    print_RL(a);
    printf("\n%d",length(a));
    reverse_list(&a);
    printf("\nReversed : \n");
    free_list(&a);
    print_LR(a);
}

