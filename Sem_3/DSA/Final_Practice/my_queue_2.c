#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *next;
}node;

typedef node* list;

typedef struct queue{
    list l;
    node *front;
    node *rear;
}queue;

void init_list(list *head){
    *head = NULL;
    return;
}

void init_queue(queue *q){
    init_list(&(q->l));
    q->front = q->rear = NULL;
    return;
}

void insert(list *head, int d){
    node *newnode = (node * ) malloc(sizeof(node));
    if(newnode){
        newnode->data= d;
        newnode->next = NULL;
    }

    if(*head == NULL){
        *head = newnode;
        return;
    }

    node *p = *head;

    while(p->next){
        p = p->next;
    }

    p->next = newnode;
    return;
}

void delete(list *head){
    if(*head == NULL){
        return;
    }
    node *p = *head;
    node *q;
    while(p->next){
        q = p;
        p = p->next;
    }
    q->next = NULL;
    free(p);
    return;
}

/*void enqueue(queue *q, int d){
    insert(&(q->l),d);
    if(q->rear == NULL){
        q->rear = q->front = q->l  ;
    }else{
        q->rear = q->rear->next;
    }
}

int dequeue(queue *q){
    if(q->front == NULL){
        return -1;
    }else{
        int d = q->front->data;
        delete(&(q->l));
        q->front= q->l;
        if(q->front == NULL){
            q->rear == NULL;
        }
        return d;
        
    }
}

void display(list *head){
    node *p = *head;

    while(p){
        printf("%d ",p->data);
        p = p->next;
    }
    return;
}
*/

void enqueue(queue *q, int d){
    insert(&(q->l),d);
    if(q->rear == NULL){
        q->rear = q->front = q->l;
    }else{
        q->rear = q->rear->next;
    }
    return;
}

int dequeue(queue *q){
    int d = q->l->data;
    delete(&(q->l));
    if(q->front == NULL){
        return -1;
    }
    q->front = q->l;
    if(q->front == NULL){
        q->rear = NULL;
    }
    return d;
}

void display(list *head){
    node *p = *head;
    while(p){
        printf("%d ",p->data);
        p = p->next;
    }

    return;

}

int main(){
    queue q;
    init_queue(&q);
    enqueue(&q,1);
    enqueue(&q,2);
    enqueue(&q,3);
    enqueue(&q,4);
    dequeue(&q);
    display(&(q.l));

    return 0;
}


