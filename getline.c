#include "shell.h"

int custom_getline(char **lineptr, size_t *n, FILE *stream) {
    int c, i;
    size_t len = 0;
    char *line = *lineptr;

    if (line == NULL || *n == 0) {
        *lineptr = malloc(128);
        if (*lineptr == NULL) {
            return -1;
        }
        *n = 128;
        line = *lineptr;
    }

    for (i = 0;; i++) {
        c = fgetc(stream);

        if (c == EOF) {
            break;
        }

        if (len + 1 >= *n) {
            *lineptr = realloc(*lineptr, *n + 128);
            if (*lineptr == NULL) {
                return -1;
            }
            *n += 128;
            line = *lineptr + len;
        }

        line[i] = c;
        len++;

        if (c == '\n') {
            break;
        }
    }

    line[i] = '\0';

    if (len == 0) {
        return -1;
    } else {
        return len;
    }
}