#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_COMMAND_LENGTH 1024

int main() {
    char command[MAX_COMMAND_LENGTH];
    char *args[2];
    args[1] = NULL;
    
    while (1) {
        printf("#cisfun$ ");
        
        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
            // end of file reached
            exit(0);
        }
        
        // remove newline character from input
        command[strcspn(command, "\n")] = '\0';
        
        args[0] = strtok(command, " ");
        
        if (execvp(args[0], args) == -1) {
            printf("%s: No such file or directory\n", args[0]);
        }
    }
    
    return 0;
}
