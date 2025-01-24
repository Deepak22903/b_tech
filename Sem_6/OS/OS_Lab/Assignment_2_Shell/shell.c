#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>

#define MAX_CMD_LEN 1024

// Global variable for custom prompt
char* PS1 = "\\w$ ";

void execute_command(char *cmd, char *args[], int background);
void change_prompt(char *new_prompt);
void set_path_variable(char *path_value);
void handle_redirection(char **args);
int parse_input(char *input, char **args);

int main() {
    char input[MAX_CMD_LEN];
    char *args[MAX_CMD_LEN / 2 + 1];  // max arguments
    int background;
    
    while (1) {
        // Show prompt
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        printf("%s %s ", PS1, cwd);
        
        // Get user input
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;  // Exit on Ctrl-D
        }
        
        // Remove newline character
        input[strcspn(input, "\n")] = 0;
        
        // Parse input
        background = parse_input(input, args);
        
        // Handle exit command
        if (strcmp(args[0], "exit") == 0) {
            break;
        }
        
        // Handle built-in commands
        if (strcmp(args[0], "cd") == 0) {
            if (chdir(args[1]) != 0) {
                perror("cd");
            }
        } else if (strcmp(args[0], "PS1") == 0) {
            change_prompt(args[1]);
        } else if (strcmp(args[0], "PATH") == 0) {
            set_path_variable(args[1]);
        } else {
            execute_command(input, args, background);
        }
    }
    
    return 0;
}

int parse_input(char *input, char **args) {
    char *token;
    int i = 0;
    int background = 0;

    // Check for background execution
    if (input[strlen(input) - 1] == '&') {
        background = 1;
        input[strlen(input) - 1] = 0;  // Remove '&' character
    }

    // Tokenize input into arguments
    token = strtok(input, " ");
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

    return background;
}

void execute_command(char *cmd, char *args[], int background) {
    pid_t pid = fork();
    
    if (pid == -1) {
        perror("fork");
        return;
    }
    
    if (pid == 0) {  // Child process
        // Handle input/output redirection
        handle_redirection(args);
        
        // Search for the executable in PATH
        char *path_env = getenv("PATH");
        if (path_env != NULL) {
            char *paths = strtok(path_env, ":");
            while (paths != NULL) {
                char full_path[MAX_CMD_LEN];
                snprintf(full_path, sizeof(full_path), "%s/%s", paths, args[0]);
                
                if (access(full_path, X_OK) == 0) {
                    execv(full_path, args);
                    perror("execv");  // If execv fails
                    exit(1);
                }
                paths = strtok(NULL, ":");
            }
        }
        
        // If command not found in PATH
        fprintf(stderr, "%s: command not found\n", cmd);
        exit(1);
    } else {  // Parent process
        if (!background) {
            wait(NULL);  // Wait for child process to complete
        }
    }
}

void change_prompt(char *new_prompt) {
    PS1 = new_prompt;
}

void set_path_variable(char *path_value) {
    setenv("PATH", path_value, 1);
}

void handle_redirection(char **args) {
    int fd;
    int i = 0;
    
    while (args[i] != NULL) {
        if (strcmp(args[i], ">") == 0) {
            // Output redirection
            fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1) {
                perror("open");
                exit(1);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
            args[i] = NULL;  // Terminate the args array at '>'
            break;
        } else if (strcmp(args[i], "<") == 0) {
            // Input redirection
            fd = open(args[i + 1], O_RDONLY);
            if (fd == -1) {
                perror("open");
                exit(1);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
            args[i] = NULL;  // Terminate the args array at '<'
            break;
        }
        i++;
    }
}
