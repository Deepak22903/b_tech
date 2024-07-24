#include<stdio.h>
#include<stdlib.h>
#include"poly.h"
void init(list *head){
	*head = NULL;
	//printf("Inintiated\n");
	return;
}

void append(list *head, int c, int e){
	node *p,*nn;
	p = *head;
	nn = (node*)malloc(sizeof(node));
	if(nn){
		nn -> coef = c;
		nn -> exponent = e;
		nn -> next = NULL;	
	}
	if(*head == NULL){
		*head = nn;
		return;
	}
	while(p -> next != NULL){
		p = p -> next;
	}
	p -> next = nn;
	return;
}

void add(list *head, list *L1, list *L2){
	node *p, *q,*nn;
	p = *L1;
	q = *L2;
	while(p && q){
		if(p->exponent == q->exponent){
			append(head, p->coef + q->coef, p->exponent);
			p = p -> next;
			q = q -> next;	
		}else if (p->exponent > q->exponent){
            append(head, p->coef, p->exponent);
            p = p->next;
        }else{
            append(head, q->coef, q->exponent);
            q = q->next;
        } 
 	}
    while (p){
		append(head, p->coef, p->exponent);
		p = p->next;
   	}
   	while (q){
		append(head, q->coef, q->exponent);
		q = q->next;
    }	
}

void sub(list *head, list *L1, list *L2){
	node *p, *q,*nn;
	p = *L1;
	q = *L2;
	while(p && q){
		if(p->exponent == q->exponent){
			append(head, p->coef - q->coef, p->exponent);
			p = p -> next;
			q = q -> next;	
		}else if (p->exponent > q->exponent){
            append(head, p->coef, p->exponent);
            p = p->next;
        }else{
            append(head, q->coef, q->exponent);
            q = q->next;
        } 
 	}
    while (p){
		append(head, p->coef, p->exponent);
		p = p->next;
   	}
   	while (q){
		append(head, q->coef, q->exponent);
		q = q->next;
    }	
}

void display(list *head){
	node *p;
	p = *head;
	if(*head == NULL){
		printf("Polynomial is empty\n");
		return;
	}
	printf("Polynomial:");
	while(p){
		if(p ->exponent == 0){
			printf("%d", p -> coef);
			p = p -> next;
			continue;
			
		}
		if(p ->exponent == 1){
			printf("%dx", p -> coef);
			p = p -> next;
			if(p -> coef < 0){
				continue;
			}
			printf("+");
			continue;
		}
		
		printf("%dx^%d", p -> coef, p ->exponent);
		p = p -> next;
		if(p != NULL){
			if(p -> coef < 0){
				continue;
			}
			printf("+");
		}
	}
	printf("\n");
}
