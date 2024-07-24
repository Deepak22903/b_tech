#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node *next;
}Node;

typedef struct cq{
    struct Node *front, *rear;
}cq;

void initQueue(cq *queue){
    queue->front = queue->rear = NULL;
    return;
}

void enqueue(cq *queue, int data){
    Node *newNode = (Node *) malloc(sizeof(Node));
    if(newNode){
        newNode->data = data;
        newNode->next = NULL;
    } else return;

    if(queue->front == NULL && queue->rear == NULL){
        queue->front = queue->rear = newNode;
        return;
    }

    queue->rear->next = newNode;
    queue->rear = newNode;
    return;
}

int dequeue(cq *queue){
    if(queue->front == NULL){
        return -1;
    }

    Node *temp = queue->front;
    int dequeuedElement = temp->data;

    if(queue->front == queue->rear){
        queue->front = queue->rear = NULL;
    }

    queue->front = queue->front->next;
    free(temp);
    return dequeuedElement;
}

int main(){
    cq q1;
    initQueue(&q1);

    int noQueries,queryType,queryValue;

    printf("Enter no. of queries: ");
    scanf("%d", &noQueries);

    for(int i = 0; i < noQueries; i++){
        printf("Enter query type(1 for enqueue & 2 for dequeue): ");
        scanf("%d",&queryType);
        if(queryType == 1){
            printf("Enter the element to enqueue: ");
            scanf("%d",&queryValue);
            enqueue(&q1,queryValue);
        }else if(queryType == 2){
            int dequeuedElement = dequeue(&q1);
            if(dequeuedElement != -1){
                printf("Dequeued Element = %d\n",dequeuedElement);
            }
        }
    }
    return 0;
}