#include <stdio.h>

int size(){
    int a = 22;
    float b = 9.03;
    double c = 69.696969;
    char d = 'D';
    char string[]="Deepak";

    printf("\nSize of Integer : %d", sizeof(a));
    
    printf("\nSize of Float : %d", sizeof(b));

    printf("\nSize of Double : %d", sizeof(c));

    printf("\nSize of Character : %d", sizeof(d));

    printf("\nSize of String(with 6 char) : %d\n", sizeof(string));

    return 0;
}