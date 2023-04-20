#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_ARGS 64

extern char **environ; // declare the environ variable

int main() {
    char *path = getenv("PATH");
    char *line = NULL;
    size_t line_size = 0;

    while (1) {
        printf("$ ");

        if (getline(&line, &line_size, stdin) == -1) {
            // end of file reached or error reading input
            free(line);
            exit(0);
        }

        int arg_count = 0;
        char *args[MAX_ARGS];
        char *token = strtok(line, " \t\n");
        while (token != NULL && arg_count < MAX_ARGS - 1) {
            args[arg_count] = token;
            arg_count++;
            token = strtok(NULL, " \t\n");
        }
        args[arg_count] = NULL;

        if (arg_count == 0) {
            // empty command line
            continue;
        }

        // check if the command is "exit"
        if (strcmp(args[0], "exit") == 0) {
            free(line);
            exit(0);
        }

        // check if the command is "env"
        if (strcmp(args[0], "env") == 0) {
            // print out the environment variables
            char **env = environ;
            while (*env != NULL) {
                printf("%s\n", *env);
                env++;
            }
            continue;
        }

        char *path_copy = strdup(path); // create a copy of the PATH variable
        char *path_token = strtok(path_copy, ":");
        while (path_token != NULL) {
            char path_command[1024];
            snprintf(path_command, sizeof(path_command), "%s/%s", path_token, args[0]);
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

    free(line);
    return 0;
}
