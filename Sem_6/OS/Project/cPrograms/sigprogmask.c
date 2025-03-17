#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  sigset_t new, old;

  sigemptyset(&new);

  sigaddset(&new, SIGINT);

  sigprocmask(SIG_BLOCK, &new, &old);
  printf("SIGINT blocked for 5 seconds\n");
  sleep(5);
  printf("SIGINT unblocked\n");
  sigprocmask(SIG_SETMASK, &old, NULL);
  while (1) {
    sleep(1);
  }

  return EXIT_SUCCESS;
}
