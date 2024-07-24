#include <stdio.h>

int main(){
    int m,n;
    printf("Enter the number of rows and columns : ");
    scanf("%d%d",&m,&n);

    for(int i = 1; i<=m; i++){
        for(int j= 4; j>=i; j--){
            printf("* ");
        }
        printf("\n");
    }
}