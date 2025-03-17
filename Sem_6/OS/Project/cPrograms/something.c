#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void printSig() {
  sigset_t mask;

  sigprocmask(SIG_SETMASK, NULL, &mask);

  printf("Printing Signals: \n");
  for (int i = 1; i < NSIG; i++) {
    if (sigismember(&mask, i)) {
      printf("%d ", i);
    }
  }
  printf("\n");
}

int main(int argc, char *argv[]) {
  sigset_t old, new;
  sigemptyset(&new);
  sigaddset(&new, SIGINT);
  sigprocmask(SIG_BLOCK, &new, &old);
  printSig();
  sigprocmask(SIG_SETMASK, &old, NULL);
  printSig();
  return EXIT_SUCCESS;
}
