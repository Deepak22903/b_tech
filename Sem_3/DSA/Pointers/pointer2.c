#include <stdio.h>

typedef struct entry {
double x;
struct entry *e;
}entry;
entry *f(entry **epp) {
entry *ep = *epp;
*epp = (entry *)malloc(sizeof(entry));
ep->e = NULL;
ep->x = 1.2;
return *epp;
}
int main() {
entry e, *ep, *eq;
ep = &e;
e.e = (entry *)malloc(sizeof(entry));
eq = f(&(e.e));
e.x = eq->x;
printf("%f",e.x);
}