#include <stdio.h>

int main(){
    char ci,co;
    int a;

    printf("\nEnter a Lower case character : ");
    scanf("%c",&ci);

    co = ci -32;
    printf("\nUppercase Letter = %c\n",co);
    return 0;
}
