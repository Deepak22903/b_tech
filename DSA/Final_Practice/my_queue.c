#include <stdio.h>
#include <stdlib.h>

typedef struct queue {
    int front;
    int rear;
    int size;
    int *Q;
}queue;

void init(queue *q, int len){
    q->Q = (int *) malloc(len * sizeof(int));
    q->front = q->rear = -1;
    q->size = len;
}

int isFull(queue q){
    if(q.rear == q.size-1){
        return 1;
    }else{
        return 0;
    }
}

int isEmpty(queue q){
    if(q.front == q.rear){
        return 1;
    }else{
        return 0;
    }
}

void enqueue(queue *q, int d){
    if(!isFull(*q)){
        q->rear++;
        q->Q[q->rear] = d;
    }
    return;
}

int dequeue(queue *q){
    if(!isEmpty(*q)){
        int d = q->Q[q->front];
        q->front++;
        return d;
    }
}

void display(queue q){
    
    if(!isEmpty(q)){
        while(q.front < q.rear){
            printf("%d ",q.Q[q.front]);
            q.front++;
        }
    }
    return;
}

int main(){
    queue a;
    init(&a,5);
    enqueue(&a,1);
    enqueue(&a,2);
    enqueue(&a,3);
    dequeue(&a);
    display(a);
}
