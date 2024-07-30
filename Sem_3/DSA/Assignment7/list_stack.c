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
    node *nn = (node *) malloc(sizeof(node));
    if(nn){
        nn->data = d;
        nn->next = NULL;
    }else return;

    if(*head == NULL){
        *head = nn;
        return;
    }

    nn->next = *head;
    *head = nn;
    return;
}

void delete(list *head){
    if(*head == NULL){
        return;
    }
    node *p = *head;
    *head = (*head)->next;
    free(p);
    return;
}

void init_stack(stack *s){
    init_list(&(s->l));
    s->top = NULL;
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
}

int pop(stack *s){
    if(!isEmpty(*s)){
        int d = s->l->data;
        delete(&(s->l));
        s->top = s->l;
        return d;
    }else return -1;
}

void print_stack(stack *s){
    while(s->top){
        printf(" %d \n",pop(s));
    }
    return;
}

/*void print_l(list l){
    node *p = l;
    while(p->data){
        printf("%d ",p->data);
        p = p->next;
    }
    return;
}*/

void main(){
    /*list a;
    init_list(&a);
    insert(&a,1);
    insert(&a,2);
    insert(&a,3);
    delete(&a);
    print_l(a);*/
    stack s;
    init_stack(&s);
    push(&s,1);
    push(&s,2);
    push(&s,3);
    print_stack(&s);
    return;
}