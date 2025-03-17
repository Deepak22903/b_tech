#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handler(int sig) { printf("Received signal %d\n", sig); }

int main() {
  signal(SIGUSR1, handler);
  printf("Raising SIGUSR1...\n");
  raise(SIGUSR1);
  printf("Signal handled successfully!\n");
  return 0;
}
