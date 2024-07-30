#include <stdio.h>


void main() {
int *p, a[4], *q, x;
p = &a[1];
q = p + 2;
x = q - p;
printf("%d",x);
}