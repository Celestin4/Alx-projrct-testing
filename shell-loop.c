#include "shell.h"
struct alias_node {
    char *alias;
    char *command;
    struct alias_node *next;
};

static struct alias_node *alias_head = NULL;
int get_exit_status();




void add_alias(char *alias, char *command) {
    struct alias_node *new_node = malloc(sizeof(struct alias_node));
    new_node->alias = strdup(alias);
    new_node->command = strdup(command);
    new_node->next = alias_head;
    alias_head = new_node;
}

char *get_alias(char *alias) {
    struct alias_node *current = alias_head;
    while (current != NULL) {
        if (strcmp(current->alias, alias) == 0) {
            return current->command;
        }
        current = current->next;
    }
    return NULL;
}

void execute_external_command(char **args, char *path) {
    char *path_copy = strdup(path);
    char *path_token = my_strtok(path_copy, ":");
    while (path_token != NULL) {
        char path_command[1024];
        snprintf(path_command, sizeof(path_command), "%s/%s", path_token, args[0]);
        if (access(path_command, X_OK) == 0) {
            if (fork() == 0) {
                execvp(path_command, args);
                perror("Error");
                exit(errno);
            } else {
                wait(NULL);
                break;
            }
        }
        path_token = my_strtok(NULL, ":");
    }
    free(path_copy);
}
