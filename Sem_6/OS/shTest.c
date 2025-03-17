#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  char arr[1024];
  int cpid;
  while (1) {
    printf("Prompt> ");
    scanf("%s", arr);
    cpid = vfork();
    if (cpid == 0) {
      execv(arr, NULL);
    } else {
      wait(NULL);
    }
  }
  return 0;
}
