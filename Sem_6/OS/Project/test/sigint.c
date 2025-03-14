#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handle_sig(int signo) {
  printf("Signal Caught: %d", signo);
  exit(0);
  return;
}

int main(int argc, char *argv[]) {
  // raise(SIGTERM);
  signal(SIGINT, handle_sig);
  while (1)
    ;
  return 0;
}
