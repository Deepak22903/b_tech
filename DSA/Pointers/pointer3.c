#include <stdio.h>

typedef struct entry {
double x;
struct entry *e;
}entry;
typedef entry *seq;
void f(seq *p) {
int i;
seq r;
*p = (seq) malloc(sizeof(entry));
r = *p;
r->x = 100.0;
for(i = 0; i < 2; i++) {
r = (seq) malloc(sizeof(entry));
(*p)->e = r;
r->e = NULL;
r->x = (double) i;
(*p) = (*p)->e;
}
}
int main() {
entry *r;
f(&r);
r = r->e;
}