#include <stdio.h>

int factorial(int n){
    if(n==1){
        return 1;
    } else{
        return n * factorial(n-1);
    }
}

int main(){
    int x,n;
    float sum;
    printf("Enter values of x and n : ");
    scanf("%d%d",&x,&n);
    sum=0;


    for(int i = 1; i <= n; i++){
        sum +=(float) x/factorial(i);

    }

    printf("Sum = %.2f",sum);
}