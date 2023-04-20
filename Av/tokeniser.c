#include "shell.h"



char *my_strtok(char *str, const char *delim) {
    static char *last_token = NULL;
    char *token = NULL;

    if (str != NULL) {
        last_token = str;
    }

    if (last_token == NULL) {
        return NULL;
    }

    token = last_token;
    while (*last_token != '\0') {
        if (strchr(delim, *last_token) != NULL) {
            *last_token++ = '\0';
            break;
        }
        last_token++;
    }

    if (*token == '\0') {
        return NULL;
    } else {
        return token;
    }
}
