#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
} Queue;

void initQueue(Queue* q) {
    q->front = q->rear = NULL;
}

int isQueueEmpty(Queue* q) {
    return q->front == NULL;
}

void enqueue(Queue* q, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        return;
    }
    newNode->data = data;
    newNode->next = NULL;

    if (isQueueEmpty(q)) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

int dequeue(Queue* q) {
    if (isQueueEmpty(q)) {
        printf("Queue is empty\n");
        return -1;
    }

    int data = q->front->data;

    Node* temp = q->front;
    q->front = q->front->next;
    free(temp);

    if (!q->front) {
        q->rear = NULL;
    }

    return data;
}

typedef struct {
    Queue q1;
    Queue q2;
} StackUsingQueues;

void initStack(StackUsingQueues* stack) {
    initQueue(&(stack->q1));
    initQueue(&(stack->q2));
}

void push(StackUsingQueues* stack, int data) {
    if (!isQueueEmpty(&(stack->q1))) {
        enqueue(&(stack->q1), data);
    } else {
        enqueue(&(stack->q2), data);
        while (!isQueueEmpty(&(stack->q1))) {
            enqueue(&(stack->q2), dequeue(&(stack->q1)));
        }
        Queue temp = stack->q1;
        stack->q1 = stack->q2;
        stack->q2 = temp;
    }
}

int pop(StackUsingQueues* stack) {
    if (isQueueEmpty(&(stack->q1))) {
        printf("Stack is empty\n");
        return -1;
    }

    return dequeue(&(stack->q1));
}

void displayStack(StackUsingQueues* stack) {
    if (isQueueEmpty(&(stack->q1))) {
        printf("Stack is empty\n");
        return;
    }

    printf("Stack: ");
    Node* current = stack->q1.front;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    StackUsingQueues myStack;
    initStack(&myStack);

    push(&myStack, 1);
    push(&myStack, 2);
    push(&myStack, 3);

    displayStack(&myStack);

    int poppedItem = pop(&myStack);
    if (poppedItem != -1) {
        printf("Popped item: %d\n", poppedItem);
    }

    displayStack(&myStack);

    return 0;
}
