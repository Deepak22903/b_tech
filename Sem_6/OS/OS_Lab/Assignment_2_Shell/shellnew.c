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
#include <signal.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 64

// Global variable to store custom prompt
char custom_prompt[MAX_COMMAND_LENGTH] = "";
// Global flag to indicate if custom prompt is set
int custom_prompt_set = 0;

// Global variable to store PATH
#define MAX_PATH_DIRS 64
char *shell_path[MAX_PATH_DIRS] = {"/usr/bin", "/bin", "/sbin"};  // Default PATH
int shell_path_count = 3;

// Function to free existing PATH
void free_path() {
    for (int i = 0; i < shell_path_count; i++) {
        // Only free if it's not a default path
        if (i >= 3) {
            free(shell_path[i]);
            shell_path[i] = NULL;
        }
    }
    shell_path_count = 3;  // Reset to default
}

// Function to handle PATH command
int handle_path_command(char **args) {
    // Check if it's a PATH command
    if (strncmp(args[0], "PATH=", 5) == 0) {
        // Free existing custom PATH
        free_path();
        
        // Extract the path string
        char *path_str = args[0] + 5;
        char *path_copy = strdup(path_str);  // Create a copy to avoid modifying original
        
        // Split path into directories
        char *token = strtok(path_copy, ":");
        while (token != NULL && shell_path_count < MAX_PATH_DIRS) {
            // For custom paths (beyond default), allocate memory
            if (shell_path_count >= 3) {
                shell_path[shell_path_count] = strdup(token);
            } else {
                shell_path[shell_path_count] = token;
            }
            shell_path_count++;
            token = strtok(NULL, ":");
        }
        
        // Free the copy of path string
        free(path_copy);
        
        return 1;  // Indicates PATH command was handled
    }
    
    return 0;  // Not a PATH command
}

// Custom function to find executable path
char* find_executable(const char *command) {
    // If command contains a slash, it's likely a full or relative path
    if (strchr(command, '/') != NULL) {
        if (access(command, X_OK) == 0) {
            return strdup(command);
        }
        return NULL;
    }
    
    // Search through each directory in PATH
    for (int i = 0; i < shell_path_count; i++) {
        // Construct full path
        char full_path[MAX_COMMAND_LENGTH];
        snprintf(full_path, sizeof(full_path), "%s/%s", shell_path[i], command);
        
        // Check if executable exists and is executable
        if (access(full_path, X_OK) == 0) {
            return strdup(full_path);
        }
    }
    
    // Executable not found
    return NULL;
}


// Enhanced redirection handling with support for multiple redirections
void handle_redirection(char **args) {
    int in_fd = -1, out_fd = -1;
    int i, j;
    
    for (i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], ">") == 0 || strcmp(args[i], ">>") == 0) {
            // Output redirection
            int flags = (strcmp(args[i], ">") == 0) 
                ? O_WRONLY | O_CREAT | O_TRUNC 
                : O_WRONLY | O_CREAT | O_APPEND;
            
            out_fd = open(args[i+1], flags, 0644);
            if (out_fd == -1) {
                perror("open output");
                exit(EXIT_FAILURE);
            }
            
            dup2(out_fd, STDOUT_FILENO);
            close(out_fd);
            
            // Remove redirection tokens
            for (j = i; args[j] != NULL; j++) {
                args[j] = args[j+2];
            }
            i -= 2;  // Adjust index to recheck current position
        }
        else if (strcmp(args[i], "<") == 0) {
            // Input redirection
            in_fd = open(args[i+1], O_RDONLY);
            if (in_fd == -1) {
                perror("open input");
                exit(EXIT_FAILURE);
            }
            
            dup2(in_fd, STDIN_FILENO);
            close(in_fd);
            
            // Remove redirection tokens
            for (j = i; args[j] != NULL; j++) {
                args[j] = args[j+2];
            }
            i -= 2;  // Adjust index to recheck current position
        }
    }
}


// Function to generate prompt
char* generate_prompt() {
    static char prompt[MAX_COMMAND_LENGTH];
    
    // If custom prompt is set, use it
    if (custom_prompt_set) {
        strcpy(prompt, custom_prompt);
        return prompt;
    }
    
    // Default prompt with current working directory
    char cwd[MAX_COMMAND_LENGTH];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        snprintf(prompt, sizeof(prompt), "%s$ ", cwd);
    } else {
        // Fallback if getcwd fails
        strcpy(prompt, "shell$ ");
    }
    
    return prompt;
}

// Function to handle PS1 command
int handle_ps1_command(char **args) {
    // Check if it's a PS1 command
    if (strncmp(args[0], "PS1=", 4) == 0) {
        // Extract the prompt string
        char *prompt_str = args[0] + 4;
        
        // Remove quotes if present
        if ((prompt_str[0] == '"' && prompt_str[strlen(prompt_str)-1] == '"') ||
            (prompt_str[0] == '\'' && prompt_str[strlen(prompt_str)-1] == '\'')) {
            prompt_str[strlen(prompt_str)-1] = '\0';
            prompt_str++;
        }
        
        // Special case for "\w$"
        if (strcmp(prompt_str, "\\w$") == 0) {
            // Reset to default (current working directory prompt)
            custom_prompt_set = 0;
            custom_prompt[0] = '\0';
        } else {
            // Set custom prompt
            strncpy(custom_prompt, prompt_str, sizeof(custom_prompt) - 1);
            custom_prompt[sizeof(custom_prompt) - 1] = '\0';
            custom_prompt_set = 1;
        }
        
        return 1;  // Indicates PS1 command was handled
    }
    
    return 0;  // Not a PS1 command
}

// Function to print error message
void print_error(const char *msg) {
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
}

// Function to split command into arguments
int parse_command(char *command, char **args) {
    int arg_count = 0;
    char *token;
    
    // Remove trailing newline
    command[strcspn(command, "\n")] = 0;
    
    // Split command into tokens
    token = strtok(command, " ");
    while (token != NULL && arg_count < MAX_ARGS - 1) {
        args[arg_count++] = token;
        token = strtok(NULL, " ");
    }
    
    // Null terminate the argument list
    args[arg_count] = NULL;
    
    return arg_count;
}

// Built-in command to change directory
int change_directory(char **args) {
    if (args[1] == NULL) {
        // If no argument, change to home directory
        if (chdir(getenv("HOME")) != 0) {
            print_error("cd");
            return -1;
        }
    } else {
        // Change to specified directory
        if (chdir(args[1]) != 0) {
            print_error("cd");
            return -1;
        }
    }
    return 0;
}

// Modified execute_command to use find_executable
int execute_command(char **args) {
    // Check for built-in commands
    if (strcmp(args[0], "cd") == 0) {
        return change_directory(args);
    }
    
    // Find executable path
    char *executable_path = find_executable(args[0]);
    if (executable_path == NULL) {
        fprintf(stderr, "%s: command not found\n", args[0]);
        return -1;
    }
    
    // Fork a child process to execute the command
    pid_t pid = fork();
    
    if (pid < 0) {
        // Fork failed
        print_error("fork");
        free(executable_path);
        return -1;
    } else if (pid == 0) {

        // Handle input/output redirection
        handle_redirection(args);

        // Child process
        // Execute the command with full path
        execv(executable_path, args);
        
        // If execv returns, it must have failed
        print_error("execv");
        free(executable_path);
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
        
        // Free the allocated executable path
        free(executable_path);
        
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        }
    }
    
    return 0;
}

int main() {
    char command[MAX_COMMAND_LENGTH];
    char *args[MAX_ARGS];
    
    while (1) {
        // Use generate_prompt() to get the current prompt
        printf("%s", generate_prompt());
        
        // Read command from user
        if (fgets(command, sizeof(command), stdin) == NULL) {
            break;  // Exit on EOF
        }
        
        // Skip empty lines
        if (command[0] == '\n') {
            continue;
        }
        
        // Exit shell if user types 'exit'
        if (strcmp(command, "exit\n") == 0) {
            break;
        }
        
        // Parse command into arguments
        int arg_count = parse_command(command, args);
        
        // Check for PS1 command first
        if (arg_count > 0 && handle_ps1_command(args)) {
            continue;  // PS1 command handled, continue to next iteration
        }
        
        // Check for PATH command
        if (arg_count > 0 && handle_path_command(args)) {
            continue;  // PATH command handled, continue to next iteration
        }
        
        // Special handling for echo command to show PATH
        if (arg_count > 0 && strcmp(args[0], "echo") == 0) {
            if (arg_count > 1 && strcmp(args[1], "$PATH") == 0) {
                // Construct PATH string from shell_path
                char path_str[MAX_COMMAND_LENGTH] = "";
                for (int i = 0; i < shell_path_count; i++) {
                    if (i > 0) {
                        strcat(path_str, ":");
                    }
                    strcat(path_str, shell_path[i]);
                }
                printf("%s\n", path_str);
            } else {
                // Default echo behavior for other arguments
                if (arg_count > 1) {
                    printf("%s\n", args[1]);
                }
            }
            continue;
        }
        
        // Execute command
        if (arg_count > 0) {
            execute_command(args);
        }
    }
    
    // Free allocated memory
    for (int i = 0; i < shell_path_count; i++) {
        free(shell_path[i]);
    }
    
    return 0;
}
