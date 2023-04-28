#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 64

int main(int argc, char *argv[]) {
    int interactive = 1;
    char input[MAX_INPUT_SIZE];
    char *args[MAX_ARGS];

    if (argc > 1) {
        interactive = 0;
        strncpy(input, argv[1], MAX_INPUT_SIZE - 1);
    }

    while (1) {
        char *token;
        int i = 0;
        pid_t pid;
        
        if (interactive) {
            printf("myshell> ");
            if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
                break;
            }
            input[strcspn(input, "\n")] = '\0';
        }

        
        pid = fork();
        if (pid < 0) {
            perror("fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            token = strtok(input, " ");
            while (token != NULL) {
                args[i] = token;
                token = strtok(NULL, " ");
                i++;
            }
            args[i] = NULL;

            execvp(args[0], args);
            perror("execvp failed");
            exit(EXIT_FAILURE);
        } else {
            wait(NULL);
        }

        memset(input, 0, MAX_INPUT_SIZE);
        memset(args, 0, sizeof(args));
    }

    return 0;
}
