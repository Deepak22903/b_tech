#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *next;
}node;

typedef node* list;

typedef struct stack{
    list l;
    node *top;
}stack;

void init_list(list *l){
    *l = NULL;
    return;
}

void insert(list *l, int d){
    node *nn= (node *) malloc(sizeof(node));
    if(nn){
        nn->data = d;
        nn->next = NULL;
    } else return;

    nn->next = *l;
    *l = nn;

    return;
}

void delete(list *l){
    if(*l == NULL){
        return;
    }

    node *p = *l;
    *l = p->next;
    free(p);
    return;
}

int isEmpty(stack s){
    if(s.top == NULL){
        return 1;
    }else{
        return 0;
    }
}

void push(stack *s, int d){
    insert(&(s->l),d);
    s->top = s->l;
    return;
}

int peek(stack s){
    if(isEmpty(s)){
        return -1;
    }else return (s.top)->data;
}

int pop(stack *s){
    if(isEmpty(*s)){
        return -1;
    }
    int d = peek(*s);
    delete(&(s->l));
    s->top=s->l;
    return d;
}

void display(list l){
    node *p = l;

    if(l == NULL){
        return;
    }

    printf("[");
    while(p){
        printf("%d ",p->data);
        p=p->next;
    }
    printf("]");

    return;
}

void init_stack(stack *s){
    init_list(&(s->l));
    s->top = NULL;
    return;
}


void display_stack(stack s){
    if(isEmpty(s)){
        return;
    }

    printf("[");
    node *p = s.top;
    while(p){
        printf("%d ",p->data);
        p = p->next;
    }
    printf("]");
    return;
}

int main(){
    stack s;
    init_stack(&s);
    push(&s,1);
    push(&s,2);
    pop(&s);
    display_stack(s);
    return 0;
}