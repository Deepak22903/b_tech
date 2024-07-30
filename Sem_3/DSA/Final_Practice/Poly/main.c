#include<stdio.h>
#include"poly.c"
int main(){
	list L1;
	list L2;
	list resultadd;
	list resultsub;
	init(&L1);
	init(&L2);
	init(&resultadd);
	init(&resultsub);
	/*append(&L1, 4,2);
	append(&L1, -5, 1);
	append(&L1, 1 , 0);
	display(&L1);
	append(&L2, 3,2);
	append(&L2, -7, 1);
	append(&L2, 4, 0);
	display(&L2);*/
	
	
	append(&L1, 2,4);
	append(&L1, 4, 1);
	append(&L1, 0 , 0);
	display(&L1);
	append(&L2, 7,3);
	append(&L2, 2, 2);
	append(&L2, 3, 1);
	append(&L2, 5, 0);
	display(&L2);
	
	add(&resultadd, &L1, &L2);
	printf("Addition of ");
	display(&resultadd);
	
	
	sub(&resultsub, &L1, &L2);
	printf("Subtraction of ");
	display(&resultsub);
	
	
	return 0;
}
