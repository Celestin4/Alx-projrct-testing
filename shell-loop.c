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

void execute_command(char *command, char *path) {
    // replace variables in the command
    char replaced_command[MAX_COMMAND_LENGTH];
    char *token = my_strtok(command, " \t\n");
    int replaced_command_length = 0;
    while (token != NULL) {
        if (token[0] == '$') {
            if (strcmp(token, "$?") == 0) {
                // replace with the exit status of the last command
                int exit_status = get_exit_status();
                char exit_status_str[16];
                snprintf(exit_status_str, sizeof(exit_status_str), "%d", exit_status);
                strcat(replaced_command, exit_status_str);
                replaced_command_length += strlen(exit_status_str);
            } else if (strcmp(token, "$$") == 0) {
                // replace with the process ID of the shell
                pid_t shell_pid = getpid();
                char shell_pid_str[16];
                snprintf(shell_pid_str, sizeof(shell_pid_str), "%d", shell_pid);
                strcat(replaced_command, shell_pid_str);
                replaced_command_length += strlen(shell_pid_str);
            } else {
                // replace with the value of the variable
                char *var_name = &token[1];
                char *var_value = getenv(var_name);
                if (var_value != NULL) {
                    strcat(replaced_command, var_value);
                    replaced_command_length += strlen(var_value);
                }
            }
        } else {
            strcat(replaced_command, token);
            replaced_command_length += strlen(token);
        }
        strcat(replaced_command, " ");
        replaced_command_length++;
        token = my_strtok(NULL, " \t\n");
    }
    replaced_command[replaced_command_length] = '\0';

    // check for alias command
    char *alias_command = get_alias(replaced_command);
    if (alias_command != NULL) {
        // execute the alias command instead
        execute_command(alias_command, path);
        return;
    }

    int arg_count = 0;
    char *args[MAX_ARGS];
    token = my_strtok(replaced_command, " \t\n");
    while (token != NULL && arg_count < MAX_ARGS - 1) {
        args[arg_count] = token;
        arg_count++;
        token = my_strtok(NULL, " \t\n");
    }
    args[arg_count] = NULL;

    if (arg_count == 0) {
        // empty command line
        return;
    }

    // execute built-in commands
    if (strcmp(args[0], "exit") == 0) {
        exit_shell();
        return;
    } else if (strcmp(args[0], "cd") == 0) {
        execute_cd(args, arg_count);
        return;
    } else if (strcmp(args[0], "setenv") == 0) {
        execute_setenv(args, arg_count);
        return;
    } else if (strcmp(args[0], "unsetenv") == 0) {
        execute_unsetenv(args, arg_count);
        return;
    }

    execute_external_command(args, path);
}



void execute_external_command(char **args, char *path) {
    // search for the command in the directories listed in path
    char *path_copy = strdup(path);
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
    free(path_copy);
}


void exit_shell() {
    exit(0);
}

void execute_cd(char **args, int arg_count) {
    // implementation of cd command
}

void execute_setenv(char **args, int arg_count) {
    // implementation of setenv command
}

void execute_unsetenv(char **args, int arg_count) {
    // implementation of unsetenv command
}