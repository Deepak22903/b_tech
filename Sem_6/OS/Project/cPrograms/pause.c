#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handle_int(int sig) { printf("Received the signal! sigNo = %d\n", sig); }

int main(int argc, char *argv[]) {
  signal(SIGINT, handle_int);
  printf("Waiting for signal\n");
  pause();
  return 0;
}
