#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *next;
}node;

typedef struct node* list;

void init(list *head){
    *head = NULL;
    return;
}

void insert_beg(list *head, int d){
    node *newnode;
    newnode = (node *) malloc(sizeof(node));
    if(newnode){
        newnode->data = d;
        newnode->next = NULL;
    }

    if(*head == NULL){
        *head = newnode;
        return;
    }

    newnode->next = *head;
    *head = newnode;
    return;
}

void insert_end(list *head, int d){
    node *newnode = (node *) malloc(sizeof(node));
    if(newnode){
        newnode->data = d;
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

void insert_pos(list *head, int pos, int d){
    node *newnode = (node *) malloc(sizeof(node));
    if(newnode){
        newnode->data = d;
        newnode->next = NULL;
    }

    if(*head == NULL){
        *head = newnode;
        return;
    }

    node *p = *head;
    int count = 0;

    while(p != NULL && count < pos-1){
        p = p->next;
        count++;
    }
    newnode->next = p->next;
    p->next = newnode;
    return;
}

void delete_begin(list *head){
    if(*head== NULL){
        return;
    }
    node *p = *head;

    *head = (*head)->next;
    free(p);
    return;
}

void delete_end(list *head){
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

void reverse_even(list *head){
    node *p = *head;
    while(p != NULL && p->next != NULL){
        if(p->data % 2 == 0 && p->next->data % 2 == 0){
            int temp = p->data;
        p->data = p->next->data;
        p->next->data = temp;
        }

        p = p->next;
    }
    return;
}

void remove_duplicates(list *head){
    node *p = *head;

    while(p != NULL && p->next != NULL){
        node *r = p;
        while(r->next){
            if(p->data == r->next->data){
            node *q = r->next;
            r->next = r->next->next;
            free(q);
            
        }else{
                r= r->next;
            }
        
        }
        p = p->next;
    }
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

void main(){
    list a;
    init(&a);
    insert_end(&a,1);
    insert_end(&a,1);
    insert_end(&a,2);
    insert_end(&a,8);
    insert_end(&a,9);
    insert_end(&a,12);
    insert_end(&a,16);
    insert_pos(&a,2,5);
    
    printf("\n\n");
    display(&a);
    reverse_even(&a);
    printf("\n");
    //display(&a);
    remove_duplicates(&a);
    //display(&a);
    return;
}