#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handle_signal(int sig) {
    printf("\nSignal %d Received!\n", sig);
    exit(EXIT_SUCCESS);
}

int main(void) {
    signal(SIGINT, handle_signal);  // Handle Ctrl+C
    printf("Waiting for signal! Press Ctrl+C to stop.\n");
    pause();
    return EXIT_SUCCESS;
}
