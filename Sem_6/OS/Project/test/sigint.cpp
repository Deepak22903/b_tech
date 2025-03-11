#include <iostream>
#include <signal.h>

using namespace std;

void handle_sig(int signo) {
  cout << "Signal Caught: " << signo << endl;
  return;
}

int main(int argc, char *argv[]) {
  // raise(SIGTERM);
  signal(SIGINT, handle_sig);
  while (1)
    ;
  return 0;
}
