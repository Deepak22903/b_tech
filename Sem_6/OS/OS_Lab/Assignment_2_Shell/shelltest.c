#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 64
#define MAX_PATH_DIRS 64

char *shell_path[MAX_PATH_DIRS] = {"/usr/bin", "/bin", "/sbin"};
int shell_path_count = 3;
char custom_prompt[MAX_COMMAND_LENGTH] = "";
int custom_prompt_set = 0;

void print_error(const char *msg) {
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
}

char* find_executable(const char *command) {
    if (strchr(command, '/') != NULL) {
        if (access(command, X_OK) == 0) {
            return strdup(command);
        }
        return NULL;
    }
    for (int i = 0; i < shell_path_count; i++) {
        char full_path[MAX_COMMAND_LENGTH];
        snprintf(full_path, sizeof(full_path), "%s/%s", shell_path[i], command);
        if (access(full_path, X_OK) == 0) {
            return strdup(full_path);
        }
    }
    return NULL;
}

void handle_redirection(char **args) {
    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], ">") == 0 || strcmp(args[i], ">>") == 0) {
            int flags = (strcmp(args[i], ">") == 0) 
                ? O_WRONLY | O_CREAT | O_TRUNC 
                : O_WRONLY | O_CREAT | O_APPEND;
            int out_fd = open(args[i+1], flags, 0644);
            if (out_fd == -1) {
                perror("open output");
                exit(EXIT_FAILURE);
            }
            dup2(out_fd, STDOUT_FILENO);
            close(out_fd);
            for (int j = i; args[j] != NULL; j++) {
                args[j] = args[j+2];
            }
            i -= 2;
        }
        else if (strcmp(args[i], "<") == 0) {
            int in_fd = open(args[i+1], O_RDONLY);
            if (in_fd == -1) {
                perror("open input");
                exit(EXIT_FAILURE);
            }
            dup2(in_fd, STDIN_FILENO);
            close(in_fd);
            for (int j = i; args[j] != NULL; j++) {
                args[j] = args[j+2];
            }
            i -= 2;
        }
    }
}

char* generate_prompt() {
    static char prompt[MAX_COMMAND_LENGTH];
    if (custom_prompt_set) {
        return custom_prompt;
    }
    char cwd[MAX_COMMAND_LENGTH];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        snprintf(prompt, sizeof(prompt), "%s$ ", cwd);
    } else {
        strcpy(prompt, "shell$ ");
    }
    return prompt;
}

int change_directory(char **args) {
    if (args[1] == NULL) {
        if (chdir(getenv("HOME")) != 0) {
            print_error("cd");
            return -1;
        }
    } else {
        if (chdir(args[1]) != 0) {
            print_error("cd");
            return -1;
        }
    }
    return 0;
}

int parse_command(char *command, char **args) {
    int arg_count = 0;
    char *token;
    command[strcspn(command, "\n")] = 0;
    token = strtok(command, " ");
    while (token != NULL && arg_count < MAX_ARGS - 1) {
        args[arg_count++] = token;
        token = strtok(NULL, " ");
    }
    args[arg_count] = NULL;
    return arg_count;
}

int handle_path_command(char **args) {
    if (strncmp(args[0], "PATH=", 5) == 0) {
        shell_path_count = 3;
        char *path_str = args[0] + 5;
        char *path_copy = strdup(path_str);
        char *token = strtok(path_copy, ":");
        while (token != NULL && shell_path_count < MAX_PATH_DIRS) {
            shell_path[shell_path_count++] = strdup(token);
            token = strtok(NULL, ":");
        }
        free(path_copy);
        return 1;
    }
    return 0;
}

int handle_ps1_command(char **args) {
    if (strncmp(args[0], "PS1=", 4) == 0) {
        char *prompt_str = args[0] + 4;
        if ((prompt_str[0] == '"' && prompt_str[strlen(prompt_str)-1] == '"') ||
            (prompt_str[0] == '\'' && prompt_str[strlen(prompt_str)-1] == '\'')) {
            prompt_str[strlen(prompt_str)-1] = '\0';
            prompt_str++;
        }
        if (strcmp(prompt_str, "\\w$") == 0) {
            custom_prompt_set = 0;
        } else {
            strncpy(custom_prompt, prompt_str, sizeof(custom_prompt) - 1);
            custom_prompt[sizeof(custom_prompt) - 1] = '\0';
            custom_prompt_set = 1;
        }
        return 1;
    }
    return 0;
}

int execute_command(char **args) {
    if (strcmp(args[0], "cd") == 0) {
        return change_directory(args);
    }
    char *executable_path = find_executable(args[0]);
    if (executable_path == NULL) {
        fprintf(stderr, "%s: command not found\n", args[0]);
        return -1;
    }
    pid_t pid = fork();
    if (pid < 0) {
        print_error("fork");
        free(executable_path);
        return -1;
    } else if (pid == 0) {
        handle_redirection(args);
        execv(executable_path, args);
        print_error("execv");
        free(executable_path);
        exit(EXIT_FAILURE);
    } else {
        int status;
        waitpid(pid, &status, 0);
        free(executable_path);
        return WIFEXITED(status) ? WEXITSTATUS(status) : -1;
    }
}

int main() {
    char command[MAX_COMMAND_LENGTH];
    char *args[MAX_ARGS];
    while (1) {
        printf("%s", generate_prompt());
        if (fgets(command, sizeof(command), stdin) == NULL) {
            break;  
        }
        if (command[0] == '\n') {
            continue;
        }
        if (strcmp(command, "exit\n") == 0) {
            break;
        }
        int arg_count = parse_command(command, args);
        if (arg_count > 0) {
            if (handle_ps1_command(args) || handle_path_command(args)) {
                continue;
            }
            if (strcmp(args[0], "echo") == 0 && arg_count > 1 && 
                strcmp(args[1], "$PATH") == 0) {
                char path_str[MAX_COMMAND_LENGTH] = "";
                for (int i = 0; i < shell_path_count; i++) {
                    if (i > 0) strcat(path_str, ":");
                    strcat(path_str, shell_path[i]);
                }
                printf("%s\n", path_str);
                continue;
            }
            execute_command(args);
        }
    }
    for (int i = 3; i < shell_path_count; i++) {
        free(shell_path[i]);
    }
    return 0;
}
