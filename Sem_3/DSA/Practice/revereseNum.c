#include <stdio.h>

int main(){
    int a,b;
    int c[1000];

    printf("Enter a number : ");
    scanf("%d",&a);

     static int i = 0;


    while(a!=0){
        b = a % 10;
        c[i]=b;
        a = a/10;
        i++;
    }

    for(int j=0; j<i;j++){
    printf("%d",c[j]);


    }
}