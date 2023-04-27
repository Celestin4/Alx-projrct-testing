#include "shell.h"

int main(void) {
    char *path = getenv("PATH");
    char *line = NULL;
    size_t line_size = 0;
    ssize_t line_length;

    while (1) {
        printf("$ ");

        if ((line_length = custom_getline(&line, &line_size, stdin)) == -1) {
            /* end of file reached or error reading input */
            free(line);
            exit(0);
        }

        /* split the line by semicolon */
        char *command = strtok(line, ";");
        while (command != NULL) {
            execute_command(command, path);
            command = strtok(NULL, ";"); /* get the next command */
        }
    }
}
