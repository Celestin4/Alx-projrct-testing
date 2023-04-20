#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_COMMAND_LENGTH 1024

int main() {
    char command[MAX_COMMAND_LENGTH];
    
    while (1) {
        printf("$ ");
        
        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
            // end of file reached
            exit(0);
        }
        
        // remove newline character from input
        command[strcspn(command, "\n")] = '\0';
        
        printf("%s: No such file or directory\n", command);
    }
    
    return 0;
}
