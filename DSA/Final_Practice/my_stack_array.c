#include <stdio.h>
#include <stdlib.h>

typedef struct stack{
    int *A;
    int size;
    int top;
}stack;

void init(stack *s, int len){
    s->A=(int *)malloc(sizeof(int)*len);
    s->size=len;
    s->top=-1;
}

int isEmpty(stack s){
    if(s.top == -1){
        return 1;
    }else{
        return 0;
    }
}

int isFull(stack s){
    if(s.top == s.size-1){
        return 1;
    }else{
        return 0;
    }
}

int pop(stack *s){
    if(isEmpty(*s)){
        return 0;
    }
    int popped_item= s->A[s->top];

    s->size--;

    return popped_item;

}

void push(stack *s,int d){
    if(isFull(*s)){
        return;
    }
    s->top++;
    s->A[s->top]=d;
    return;
}

void display(stack s){
    for(int i = 0; i< s.top+1; i++){
        printf("%d\n",s.A[i]);
    }
    return;
}

void main(){
    stack a;
    init(&a,5);
    push(&a,1);
    push(&a,2);
    push(&a,3);
    push(&a,4);
    display(a);
    pop(&a);

}