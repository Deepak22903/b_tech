#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int r;
    int c;
    int val;
    struct node *next;
}node;

typedef node* list;

void init(list *head){
    *head = NULL;
    return;
    }

void append(list *head, int r, int c, int val){
    node *newnode = (node *)malloc(sizeof(node));
    if(newnode){
        newnode->r=r;
        newnode->c=c;
        newnode->val=val;
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

void add(list *head1, list *head2, list *res){
    node *p,*q;
    p = *head1;
    q = *head2;

    while(p && q){
        if(p->r == q->r){
            if(q->c == p->c){
                append(res,p->r,p->c,p->val + q->val);
                p = p->next;
                q = q->next;
            }else if(p->c < q->c){
                append(res,p->r,p->c,p->val);
                p = p->next;
                q = q->next;
            }else{
                append(res,q->r,q->c,q->val);
                p = p->next;
                q = q->next;
            }
        } else if(p->r < q->r){
            append(res,p->r,p->c,p->val);
            p = p->next;
            q = q->next;
        }else{
            append(res,q->r, q->c, q->val);
            p = p->next;
            q = p->next;
        }
    }

    while(p){
        append(res,p->r,p->c,p->val);
        p = p->next;
    }

    while(q){
        append(res, q->r, q->c,q->val);
        q = q->next;
    }
    return;
}

void display(list *head){
    node *p = *head;

    while(p){
        printf("row = %d, column = %d, value = %d\n",p->r,p->c,p->val);
        p = p->next;
    }
    return;
}

int main(){
    FILE *fp1,*fp2,*fp3,*fp4;
    fp1 = fopen("Matrix1.txt","r");
    fp2 = fopen("Matrix2.txt","r");

    list m1;
    init(&m1);

    int row1,col1,row2,col2,temp;
    fscanf(fp1,"%d",&row1);
    fscanf(fp1,"%d",&col1);
    for(int i = 0; i < row1; i++){
        for(int j = 0; j <col1; j++){
            fscanf(fp1,"%d",&temp);
            if(temp != 0){
                append(&m1,i,j,temp);
            }
        }
    }

    list m2;
    init(&m2);

    fscanf(fp2,"%d",&row2);
    fscanf(fp2,"%d",&col2);

    for(int i = 0; i < row2; i++){
        for(int j = 0; j < col2; j++){
            fscanf(fp2,"%d",&temp);
            if(temp != 0){
                append(&m2,i,j,temp);
            }
        }
    }

    list res;
    init(&res);

    if(row1 != row2 && col1 != col2){
        printf("\nCannot Add Matrices\nrow1 = %d, row2 = %d\ncol1 = %d, col2 = %d\n\n",row1,row2,col1,col2);
    }
    add(&m1,&m2,&res);
    display(&res);
}