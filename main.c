#include "shell.h"

int main() {
    char *path = getenv("PATH");
    char *line = NULL;
    size_t line_size = 0;
    ssize_t line_length;

    while (1) {
    printf("$ ");

    if (custom_getline(&line, &line_size, stdin) == -1) {
        // end of file reached or error reading input
        free(line);
        exit(0);
    }

    // split the line by semicolon
    char *command = strtok(line, ";");
    while (command != NULL) {

        int arg_count = 0;
        char *args[MAX_ARGS];
        char *token = my_strtok(command, " \t\n");
        while (token != NULL && arg_count < MAX_ARGS - 1) {
            args[arg_count] = token;
            arg_count++;
            token = my_strtok(NULL, " \t\n");
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

        // check if the command is "setenv"
        if (strcmp(args[0], "setenv") == 0) {
            if (arg_count != 3) {
                printf("Usage: setenv VARIABLE VALUE\n");
                continue;
            }
            if (setenv(args[1], args[2], 1) == -1) {
                perror("Error");
            }
            continue;
        }

        // check if the command is "unsetenv"
        if (strcmp(args[0], "unsetenv") == 0) {
            if (arg_count != 2) {
                printf("Usage: unsetenv VARIABLE\n");
                continue;
            }
            if (unsetenv(args[1]) == -1) {
                perror("Error");
            }
            continue;
        }

        // check if the command is "cd"
        if (strcmp(args[0], "cd") == 0) {
            if (arg_count != 2) {
                printf("Usage: cd DIRECTORY\n");
                continue;
            }
            if (chdir(args[1]) == -1) {
    perror("cd");
    continue;
}

        }

        char *path_copy = strdup(path); // create a copy of the PATH variable
        char *path_token = my_strtok(path_copy, ":");
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
            path_token = my_strtok(NULL, ":");
        }
        free(path_copy); // free the memory allocated by strdup

        command = strtok(NULL, ";"); // get the next command
    }

}

}
