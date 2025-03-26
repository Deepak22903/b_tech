#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  signal(SIGSEGV, SIG_IGN);
  int arr[1] = {1};
  int a = arr[99999];
  printf("%d", a);
  return EXIT_SUCCESS;
}
