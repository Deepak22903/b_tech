#include <stdio.h>

int main(){
    int n;

    printf("Enter a number : ");
    scanf("%d",&n);

    for(int i = 1; i<=1000; i++){
        if(i % n == 0){
            printf("%d\n",i);
        }
    }
}