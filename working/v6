#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 64

int main() {
    char command[MAX_COMMAND_LENGTH];
    char *args[MAX_ARGS];
    char *path = getenv("PATH");
    
    while (1) {
        printf("$ ");
        
        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
            // end of file reached
            exit(0);
        }
        
        // remove newline character from input
        command[strcspn(command, "\n")] = '\0';
        
        int arg_count = 0;
        char *token = strtok(command, " ");
        while (token != NULL && arg_count < MAX_ARGS - 1) {
            args[arg_count] = token;
            arg_count++;
            token = strtok(NULL, " ");
        }
        args[arg_count] = NULL;
        
        if (arg_count == 0) {
            // empty command line
            continue;
        }
        
        // check if the command is "exit"
        if (strcmp(args[0], "exit") == 0) {
            exit(0);
        }
        
        char *path_copy = strdup(path); // create a copy of the PATH variable
        char *path_token = strtok(path_copy, ":");
        while (path_token != NULL) {
            char path_command[MAX_COMMAND_LENGTH];
            snprintf(path_command, MAX_COMMAND_LENGTH, "%s/%s", path_token, args[0]);
            if (access(path_command, X_OK) == 0) {
                if (fork() == 0) {
                    // child process
                    execvp(path_command, args);
                    perror("Error");
                    exit(errno);
                } else {
                    // parent process
                    wait(NULL);
                    break;
                }
            }
            path_token = strtok(NULL, ":");
        }
        free(path_copy); // free the memory allocated by strdup
    }
    
    return 0;
}
