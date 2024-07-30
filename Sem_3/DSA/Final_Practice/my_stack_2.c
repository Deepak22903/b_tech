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

void init_list(list *head){
    *head = NULL;
    return;
}

void insert(list *head, int d){
    node *newnode = (node *) malloc(sizeof(node));
    if(newnode){
        newnode->data = d;
        newnode->next = NULL;
    } else return;

    if(*head == NULL){
        *head = newnode;
        return;
    }

    newnode->next = *head;
    *head = newnode;
    return;
}

void delete(list *head){
    if(*head == NULL){
        return;
    }

    node *p = *head;
    *head = p->next;
    free(p);
    return;
}

void init_stack(stack *s){
    init_list(&(s->l));
    s->top = NULL;
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
    if(!isEmpty(s)){
        return (s.top)->data;
    }else{
        return -1;
    }
}

int pop(stack *s){
    if(!isEmpty(*s)){
        int p = peek(*s);
        delete(&(s->l));
        s->top = s->l;
        return p;
    }
    
}

void display_stack(stack *s){
    if(!isEmpty(*s)){
        while((s->top)->next){
            printf("%d ",(s->top)->data);
            (s->top) = (s->top)->next;
        }
    }
    return;
}

void display(list *head){
    node *p;
    p = *head;
    printf("[");
    while(p){
        printf("%d ", p->data);
        p = p->next;
    }
    printf("]\n");
    return;
}

int main(){
    stack s;
    push(&s,1);
    push(&s,2);
    pop(&s);
    display_stack(&s);

    return 0;
}