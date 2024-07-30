#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *next,*prev;
}node;

typedef struct list{
    node *front,*rear;
}list;

void init(list *l){
    l->front = NULL;
    l->rear = NULL;
}

void append(list *l, int d){
    node *newnode = (node *) malloc(sizeof(node));
    if(newnode){
        newnode->data = d;
        newnode->next = NULL;
        newnode->prev = NULL;
    }else return;

    if(l->front == NULL){
        l->front = newnode;
        l->rear = newnode;
    } else{
        node *p = l->front;
        while(p->next){
            p = p->next;
        }
        p->next = newnode;
        newnode->prev = p;
        l->rear = newnode;
    }
}

void display(list l){
    node *p = l.front;
    do{
        printf("%d ",p->data);
        p = p->next;
    }while(p);
    return;
}

void main(){
    list l;
    init(&l);
    append(&l,1);
    append(&l,2);
    display(l);
}