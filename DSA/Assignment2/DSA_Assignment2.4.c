#include <stdio.h>


int main(){
int num,i,count,r;
int arr[100];

printf("Enter a decimal number : ");
scanf("%d",&num);

for( i=0; num>0; i++){
    r=num % 2;
    if(r == 1){
        count++;
    }
    arr[i]=r;
    num = num/2;
}

printf("Binary Representation : ");
for(i=i-1;i>=0;i--){
printf("%d",arr[i]);
}
printf("\n");

printf("Number of 1's : %d\n",count);

}


