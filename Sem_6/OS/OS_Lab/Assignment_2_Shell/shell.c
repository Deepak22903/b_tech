#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    while (1) {
        char str[50];
        printf("prompt> ");
        scanf("%s", str);

        pid_t pid = fork();
        if (pid == -1) {
            perror("fork failed");
            return 1;
        }

        if (pid == 0) { 
            if (strcmp(str, "ls") == 0) {
                execlp("ls", "ls", NULL);
            } else {
                printf("Unknown command: %s\n", str);
                return 1;
            }
        } else { 
            wait(NULL); 
        }
    }
    return 0;
}
