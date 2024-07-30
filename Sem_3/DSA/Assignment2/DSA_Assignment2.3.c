#include <stdio.h>

int main(){
long int num;
int sum;

printf("\nEnter a number :  ");
scanf("%ld",&num);

int isEven = 0;

while(num != 0){

if(isEven % 2 == 0){
sum = sum + (num % 10);
}
num = num/10;
isEven++;
}
printf("\n\nSum = %d\n",sum);
}
