
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

typedef struct node{
	int d;
	struct node* next;

}node;

typedef node* clist;

void init(clist *l){
	*l = NULL;
	return;
}

void insert_end(clist *l,  int d){
	node *p = *l;
	node* nn = (node *)malloc(sizeof(node));
	if(nn){
		nn->d = d;
		nn->next = NULL;
	}
	else
	return;
	
	if(*l==NULL){
	nn->next=*l;
	*l=nn;
	}
	else{
	while(p->next!=*l){
		p = p->next;
	}
	p->next = nn;
	
	}
	nn->next=*l;
	
	return;
}

void insert_beg(clist *l,  int d){
	node *p;
	node *nn = (node *)malloc(sizeof(node));
	if(nn){
		nn->d = d;
		nn->next = NULL;
	
	}
	else
	return;
	if(*l==NULL){
		*l=nn;
		nn->next=*l;
	
	}
	else{
	p=*l;
	nn->next=p;
	while(p->next!=*l){
		p = p->next;
	}
	p->next = nn;
	
	}
	
	*l=nn;
	return;
}

void del_beg(clist *l){
	node *p,*q;
	if(*l==NULL)
		return;
	else
	 p = *l;
	 while(p->next != *l){
		p = p->next;
	 }
	 p->next =*l;
	 free(p);
	 return;

}

void del_end(clist *l){
	node *p,*q;
	if(*l==NULL)
		return;
	else
	 p = *l;
	 while(p->next!=*l){
	 	q=p;
	 	p=p->next;
	 }
	 free(p);
	 q->next = *l;
	 return;
}

void traverse(clist l){
    node *p = l;
    do {
        printf("%d ", p->d);
        p = p->next;
    } while (p != l && p != NULL);
    printf("\n");
    return;
}


int main()
{
clist l;
init(&l);

insert_end(&l,1);
insert_end(&l,2);
insert_beg(&l,3);
insert_beg(&l,4);
del_beg(&l);
traverse(l);



return 0;
}



