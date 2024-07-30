#include <stdio.h>

int largest(){

    int n1,n2,n3,largest;

    printf("Enter three numbers : ");
    scanf("%d %d %d", &n1, &n2, &n3);

    largest = (n1 > n2 ? (n1 > n3 ? n1 : n3) : n2 > n3 ? n2 : n3);

    printf("\nThe largest number : %d\n", largest);

    return 0;

}