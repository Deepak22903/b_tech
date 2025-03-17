#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void print_signal_mask() {
  sigset_t mask;
  sigprocmask(SIG_SETMASK, NULL, &mask); // Get current mask

  printf("Blocked signals: ");
  for (int i = 1; i < NSIG; i++) {
    if (sigismember(&mask, i)) {
      printf("%d ", i);
    }
  }
  printf("\n");
}

int main() {
  sigset_t mask;

  sigemptyset(&mask);
  sigaddset(&mask, SIGINT); // Block SIGINT (Ctrl+C)
  // sigaddset(&mask, SIGSEGV); // Block SIGINT (Ctrl+C)

  sigprocmask(SIG_BLOCK, &mask, NULL); // Apply the mask
  printf("SIGINT is now blocked.\n");
  print_signal_mask();

  sleep(5);

  sigprocmask(SIG_UNBLOCK, &mask, NULL); // Unblock SIGINT
  printf("SIGINT is now unblocked.\n");
  print_signal_mask();

  while (1)
    sleep(1); // Keep running

  return 0;
}
