#include<limits.h>
#include<stdlib.h>
#include<stdio.h>

typedef struct stack{
    int *a;
    int size;
    int top;
}stack;


void init(stack *s, int len){
    s->a = (int*)malloc(sizeof(int)*len);
    s->size = len;
    s->top = -1;
}

int isFull(stack s) {
    if(s.top == s.size-1)
        return 1;
    else
        return 0;
}

int isEmpty(stack s) {
    if(s.top == -1)
        return 1;
    else
        return 0;
}
void push(stack *s, int d){
    if(isFull(*s))
        return ;
    else {
        s->top++;
        s->a[s->top] = d;
        return;
    }
}

int pop(stack *s) {
    if (isEmpty(*s))
        return INT_MIN;
    else {
        int poppedItem = s->a[s->top];
        s->top--;
        return poppedItem;
    }
}


int main() {
    stack s1, s2;
    init(&s1,100);
    init(&s2, 10);
    int item;
    while (scanf("%d", &item) == 1 && item != -1)
        push(&s1, item);
    printf("Stack 1\n");
    while((item = pop(&s1))!= INT_MIN)
        printf("%d\n", item);
    return 0;
}
