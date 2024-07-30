#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    char d;
    struct node *next;
}node;

typedef node* list;

typedef struct queue{
    list l;
    struct node *front,*rear;
}queue;

void init_list(list *head){
    *head = NULL;
    return;
}

void append(list *head, char d){
    node *nn = (node *) malloc(sizeof(node));
    if(nn){
        nn->d = d;
        nn->next = NULL;
    } else return;

    if(*head == NULL){
        *head = nn;
        return;
    }

    node *p = *head;

    while(p->next){
        p = p->next;
    }

    p->next = nn;
    return;
}

void delete(list *head){
    node *p = *head;
    if(*head == NULL){
        return;
    }

    if(p->next == NULL){

        free(p);
        return;
    }

    node *q;

    while(p->next){
        q = p;
        p = p->next;
    }
    q->next = NULL;
    free(p);
    return;
}

void init_q(queue *q){
    init_list(&(q->l));
    q->front = q->rear = NULL;
    return;
}

int isEmpty(queue q){
    if(q.rear == NULL){
        return 1;
    }else return 0;
}

void enqueue(queue *q, char d){
    if(isEmpty(*q)){
        append(&(q->l),d);
        q->front = q->rear = q->l;
    }else{
        append(&(q->l),d);
        q->rear = q->l;
    }
    return;
    
}

int dequeue(queue *q){
    if(!isEmpty(*q)){
        int d = q->l->d;
        delete(&(q->l));
        q->front = q->l;
        return d;
    }else return -1;
    
}

void print_queue(queue *q){
    while(!isEmpty(*q)){
        printf("%d ",dequeue(q));
    }
    return;
}

void main(){
    queue q;
    init_q(&q);
    enqueue(&q,1);
    enqueue(&q,2);
    enqueue(&q,3);
    print_queue(&q);
    return;
}