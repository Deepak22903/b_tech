#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* top;
} Stack;

void initStack(Stack* stack) {
    stack->top = NULL;
}

int isStackEmpty(Stack* stack) {
    return stack->top == NULL;
}

void push(Stack* stack, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        return;
    }
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
}

int pop(Stack* stack) {
    if (isStackEmpty(stack)) {
        printf("Stack is empty\n");
        return -1;
    }

    int data = stack->top->data;
    Node* temp = stack->top;
    stack->top = stack->top->next;
    free(temp);

    return data;
}

typedef struct {
    Stack s1;
    Stack s2;
} QueueUsingStacks;

void initQueue(QueueUsingStacks* queue) {
    initStack(&(queue->s1));
    initStack(&(queue->s2));
}

int isQueueEmpty(QueueUsingStacks* queue) {
    return isStackEmpty(&(queue->s1)) && isStackEmpty(&(queue->s2));
}

void enqueue(QueueUsingStacks* queue, int data) {
    push(&(queue->s1), data);
}

int dequeue(QueueUsingStacks* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty\n");
        return -1;
    }

    if (isStackEmpty(&(queue->s2))) {
        while (!isStackEmpty(&(queue->s1))) {
            push(&(queue->s2), pop(&(queue->s1)));
        }
    }

    return pop(&(queue->s2));
}

void displayQueue(QueueUsingStacks* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty\n");
        return;
    }

    printf("Queue: ");
    while (!isStackEmpty(&(queue->s1))) {
        push(&(queue->s2), pop(&(queue->s1)));
    }

    Node* current = queue->s2.top;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    QueueUsingStacks myQueue;
    initQueue(&myQueue);

    enqueue(&myQueue, 1);
    enqueue(&myQueue, 2);
    enqueue(&myQueue, 3);

    displayQueue(&myQueue);

    int dequeuedItem = dequeue(&myQueue);
    if (dequeuedItem != -1) {
        printf("Dequeued item: %d\n", dequeuedItem);
    }

    displayQueue(&myQueue);

    return 0;
}
