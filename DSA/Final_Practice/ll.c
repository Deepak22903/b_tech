    #include <stdio.h>
    #include <stdlib.h>

    typedef struct node {
        int data;
        struct node *next;
    } node;

    typedef node* list;

    void init(list *head){
        *head = NULL;
        return;
    }

    void insert_end(list *head, int d){
        node *p, *newnode;
        newnode = (node *) malloc(sizeof(node));
        if(newnode){
            newnode->data= d;
            newnode->next = NULL;
        } else return;

        if(*head == NULL){
            *head = newnode;
            return;
        }

        p = *head;

        while(p->next){
            p = p->next;
        }

        p->next = newnode;
        return;
    }

    void insert_beg(list *head, int d){
        node *newnode;
        node *p = *head;
        newnode = (node *) malloc(sizeof(node));
        if(newnode){
            newnode->data= d;
            newnode->next=NULL;
        }

        if(*head == NULL){
            *head = newnode;
            return;
        }

        newnode->next= *head;
        *head = newnode;
        return;
    }

    void insert_pos(list *head, int pos, int val){
        node *p = *head;
        node *newnode;
        newnode = (node * ) malloc(sizeof(node));
        if(newnode){
            newnode->data = val;
            newnode->next = NULL;
        }

        if(*head == NULL || pos == 0){
            newnode->next = *head;
            *head = newnode;
            return;
        }

        int count = 0;

        while(count < pos - 1 && p != NULL){
            p = p->next;
            count++;
        }

        if(p == NULL){
            printf("Position out of bounds");
            free(newnode);
            return;
        }

        newnode->next = p->next;
        p->next = newnode;
    }

    void delete_beg(list *head){
        node *p = *head;

        if(*head == NULL){
            return;
        }

        *head = (*head)->next;
        free(p);
        return;
    }

void delete_end(list *head){
    node *p = *head;
    node *q;

    if(*head == NULL){
        return;
    }

    if(p->next == NULL){
        *head= NULL;
        return;
    }

    while(p->next){
        q = p;
        p = p->next;
    }

    q->next = NULL;
    free(p);
    return;
}

void delete_pos(list *head,int pos){
    if(*head == NULL){
        return;
    }

    if(pos == 0){
        delete_beg(head);
        return;
    }

    node *p = *head;
    node *q = NULL;
    int count = 0;

    while(p != NULL && count < pos){
        q = p;
        p = p->next;
        count++;
    }

    if(p == NULL){
        return;
    }

    q->next = p->next;
    free(p);
    return;

}

    void display(list head){
        node *p;
        p = head;

        printf("[");
        while(p){
            printf("%d ",p->data);
            p = p->next;
        }
        printf("]");
        return;
    }

    void destroy(list *head){
        node *p = *head;

        while(*head){
            *head = (*head)->next;
            free(p);
        }

    }

    node* search(list *head, int val){
        node *p = *head;
        while(p != NULL){
            if(p->data == val){
                return p;
            }
            p = p->next;
        }

        return NULL;
    }

    int length(list *head){
        node *p = *head;
        int count;

        while(p != NULL){
            count++;
            p = p->next;
        }
        return count;
    }

    int main(){
        list a;
        init(&a);
        insert_end(&a,1);
        insert_end(&a,2);
        insert_end(&a,3);
        insert_end(&a,4);
        insert_end(&a,5);
        delete_beg(&a);
        delete_end(&a);
        insert_beg(&a,1);
        //destroy(&a);
        insert_pos(&a,4,5);
        delete_pos(&a,4);
        display(a);
        printf("\n %d",search(&a,5));
        printf("\nLength : %d ",length(&a));

        return 0;
    }