#include <stdio.h>

int main(){
    int m,n;

    printf("Enter two numbers : ");
    scanf("%d",&n);
    scanf("%d",&m);

    for(int i = n; i<=m; i++){
        printf("%d\n",i);
    }
}