#include<stdio.h>
#include<stdlib.h>

typedef struct node {
    int data;
    struct node *next, *prev;
}node;

typedef struct list{
        node  *front, *rear;
}list;

void init(list *l){
    l->front = NULL;
    l->rear = NULL;
}

int isempty(list l){
    if(l.front ==NULL)
         return 1;
    return 0;
}



void insertright(list *l, int d) {
  node *newnode = (node*)malloc(sizeof(node));
  newnode->next =NULL;
  newnode->prev =NULL;
  newnode->data =d;
  if(!isempty(*l)){
     node *temp = l->front;
     while(temp->next!=NULL)
            temp = temp->next;
     temp->next = newnode;
     newnode->prev = temp;
     l->rear = newnode;
    }
  else{
     l->front = newnode;
     l->rear = newnode;
  }
}


void printlistLR(list l) {    
    node *p;
    printf("Fwd: [ ");
    p = l.front;
    if(!p) {
        printf("]\n");
        return;
    }
    do {
        printf("%d ", p->data);
        p = p->next;
    }while(p != NULL);
    printf("]\n");
}

void printlistRL(list l) {
    node *p;
    printf("BWD: [ ");
    p = l.rear;
    printf("%d ", p->data);
    if(!p) {
        printf("]\n");
        return;
    }
    do {
        printf("%d ", p->data);
        p = p->prev;
    }while(p != NULL);
    printf("]\n");


}

int length(list l){
       int count =0 ;
       node*p = l.rear;
       while(p){
             count++;
             p = p->prev;
    }
    return count;
}


void reverse(list *l){
   node  *p1, *p2;
   int temp;
   p1 = l->front; 
   p2 = l->rear;
   
   while(p1!=p2 && p2 != p1->prev){
        temp = p1->data;
        p1->data = p2->data;
        p2->data = temp;
        p1=p1->next;
        p2=p2->prev;
   }
  
}



void insertsorted(list *l,int d){
	node *newnode = (node*)malloc(sizeof(node));
        newnode->next =NULL;
        newnode->prev =NULL;
        newnode->data =d;
        if(isempty(*l)){
	    l->front=newnode;
            l->rear = newnode;
            return;
        }
        node *p = l->front;
        while(p->data<d && p->next !=NULL)
             p= p->next;
        
        if(p == l->front){
           l->front = newnode;
           newnode->next = p;
           p->prev = newnode;
           return;
        }        
        
        if(p == l->rear && p->data < d){
            l->rear =newnode;
            p->next = newnode;
            newnode->prev = p;
            return;
         }

         p=p->prev;
         printf("\n%d",p->data);
         newnode->next = p->next;
         p->next = newnode;
         newnode->prev = p;
         //p->next = newnode;
        
}


void removelist(list *l, int d){
       if(isempty(*l))
            return;
       node *p = l->front;
       while(p->data!=d && p->next)
          p= p->next;
       if(p->data == d){
              p->prev->next = p->next;
              p->next->prev = p->prev;
              free(p);
       }
}


void freelist(list *l){
      node *p = l->front;
      node * q;
      while(p){
        q= p;
        p=p->next;
        free(q);
     }
     l->front =NULL;
     l->rear =NULL;
}

void sort(list *l){
 	node *p1 =l->front;
 	node *temp=NULL;
 	int x;
 	if(!p1)
	   return;
 	node *p2 = p1->next;
 	while(p2){
      		temp = p1;  
      		x = p2->data;
      		while(temp && temp->data>x){
        		 temp->next->data =temp->data;
        		 temp = temp->prev;
      		}
      		if(!temp)
        		l->front->data =x; 
      
      		else
        		temp->next->data =x;
      		p2=p2->next;
      		p1=p1->next;
	}

}


int search(list l, int d){
     node *ptr = l.front;
     
     while (ptr)
     {
        if(ptr->data == d){
            return 1;
        }
        ptr = ptr->next;
     }
     return 0;
     
}


list listunion(const list l1, list l2){ 
       list l3;
       init(&l3);
       node* ptr1= l1.front;
       while(ptr1){
              insertright(&l3, ptr1->data);
              ptr1=ptr1->next;
       }
       
       node* ptr2 = l2.front;
       while(ptr2){
            if(!search(l3,ptr2->data)){
                 insertright(&l3, ptr2->data);
                 
            }
            ptr2=ptr2->next;
       }
                   
       return l3;
}

list listintersection(const list l1, list l2){ 
       list l3;
       init(&l3);
       node* ptr2 = l2.front;
       while(ptr2){
            if(search(l3,ptr2->data)){
                 insertright(&l3, ptr2->data);
                 
            }
            ptr2=ptr2->next;
       }
                   
       return l3;
}
            
void main(){

    list l1,l2;
    init(&l1);
    init(&l2);
    insertright(&l1,10);
    insertright(&l1,20);
    insertright(&l1,30);
    insertright(&l1,15);
    sort(&l1);
    printlistLR(l1);
    insertright(&l2,40);
    insertright(&l2,80);
    insertright(&l2,70);
    insertright(&l2,10);
    printlistLR(l2);
    list l3 = listunion(l1,l2);
    printf("\nUNION\n");
    printlistLR(l3);
    list l4 = listintersection(l1,l2);
    printf("\nINtersection\n");
    printlistLR(l4);
    printf("\n%d\n", search(l1,3));
    int len = length(l1);
    printf("%d\n", len);
    reverse(&l1);
    printlistLR(l1);
    insertsorted(&l2,80);
    insertsorted(&l2,10);
    insertsorted(&l2,40);
    insertsorted(&l2,35);
    printlistLR(l2);
    removelist(&l1, 20);
    printlistLR(l1);
    freelist(&l1);
   
}





