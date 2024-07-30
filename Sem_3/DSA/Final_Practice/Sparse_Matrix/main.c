#include<stdio.h>
#include<stdlib.h>
#include"list.c"

int main(){
	FILE *fp1, *fp2, *fp3, *fp4;
	fp1 = fopen("Matrix1.txt", "r");
	fp2 = fopen("Matrix2.txt", "r");
	int row1, col1, temp, row2, col2;
	list l1;
	init(&l1);
	fscanf(fp1, "%d", &row1);
	fscanf(fp1, "%d", &col1);
	for (int i = 0; i < row1; i++){
		for(int j = 0; j < col1; j++){
			fscanf(fp1, "%d", &temp);
			if(temp != 0){
				append(&l1, i, j, temp);
			}
		}	
	}
	
	list l2;
	init(&l2);
	fscanf(fp2, "%d", &row2);
	fscanf(fp2, "%d", &col2);
	for (int i = 0; i < row2; i++){
		for(int j = 0; j < col2; j++){
			fscanf(fp2, "%d", &temp);
			if(temp != 0){
				append(&l2, i, j, temp);
			}
		}	
	}
	if(row1 != row2 || col1 != col2){
		printf("These matrices can't be added or subtracted\n");
		return 0;
	}
	list add;
	init(&add);
	sum(&l1, &l2, &add);
	list p = add;
	fp3 = fopen("MatrixSum.txt", "a");
	fprintf(fp3, "%d\n", row1);
	fprintf(fp3, "%d\n", col1);
	for (int i = 0; i < row1; i++){
		for(int j = 0; j < col1; j++){
			if(i == p->r && j == p->c){
				fprintf(fp3, "%d ", p->val);
				p = p->next;
			}
			else fprintf(fp3, "%d ", 0);
		}
		fprintf(fp3, "\n");	
	}
	
	list min;
	init(&min);
	sub(&l1, &l2, &min);
	list q = min;
	fp4 = fopen("MatrixDiff.txt", "a");
	fprintf(fp4, "%d\n", row1);
	fprintf(fp4, "%d\n", col1);
	for (int i = 0; i < row1; i++){
		for(int j = 0; j < col1; j++){
			if(i == q->r && j == q->c){
				fprintf(fp4, "%d ", q->val);
				q = q->next;
			}
			else fprintf(fp4, "%d ", 0);
		}
		fprintf(fp4, "\n");	
	}
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
	return 0;
}
