#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(void) {
  int arr[2];
  pipe(arr);
  // printf("%d %d", arr[0], arr[1]);
  int pid = fork();
  if (pid == 0) {
    close(arr[0]);
    write(arr[1], "-al", 3);
  } else {
    close(arr[1]);
    char abc[10];
    read(arr[0], abc, 3);
    // abc[3] = '\0';
    printf("%s", abc);
    execl("/bin/eza", "eza", abc, NULL);
  }

  return EXIT_SUCCESS;
}
