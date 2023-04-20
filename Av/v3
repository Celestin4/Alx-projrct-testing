#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 64

int main() {
    char command[MAX_COMMAND_LENGTH];
    char *args[MAX_ARGS];
    
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
        
        if (execvp(args[0], args) == -1) {
            perror("Error");
        }
    }
    
    return 0;
}
