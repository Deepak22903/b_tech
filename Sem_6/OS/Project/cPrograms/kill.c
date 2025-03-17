#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage : %s <PID>\n", argv[0]);
    return 1;
  }
  pid_t pid = atoi(argv[1]);
  if (kill(pid, SIGKILL) == 0) {
    printf("Signal Sent Successfully\n");
  } else {
    perror("error\n");
  }
  return EXIT_SUCCESS;
}
