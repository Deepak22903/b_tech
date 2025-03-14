#include <stdio.h>
#include <unistd.h>
int i = 0;
int main(int argc, char *argv[]) {
  pid_t pid = vfork();
  if (pid == 0) {
    printf("printing from child\n");
    i++;
    printf("child i = %d\n", i);
    // execv("/bin/ls", NULL);
  } else {
    printf("printing from parent\n");
    i++;
    printf("parent i = %d\n", i);
  }
  // printf("Still in parent");
  return 0;
}
