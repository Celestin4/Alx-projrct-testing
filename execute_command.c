#include "shell.h"


    int get_exit_status() {
    return 0;
    }
void execute_command(char *command, char *path) {
    char replaced_command[MAX_COMMAND_LENGTH] = {0};
    char *token = my_strtok(command, " \t\n");
    int replaced_command_length = 0;
    int arg_count = 0;



    while (token != NULL) {
        if (token[0] == '$') {
            if (strcmp(token, "$?") == 0) {
                int exit_status = get_exit_status();
                char exit_status_str[16];
                snprintf(exit_status_str, sizeof(exit_status_str), "%d", exit_status);
                strcat(replaced_command, exit_status_str);
                replaced_command_length += strlen(exit_status_str);
            } else if (strcmp(token, "$$") == 0) {
                pid_t shell_pid = getpid();
                char shell_pid_str[16];
                snprintf(shell_pid_str, sizeof(shell_pid_str), "%d", shell_pid);
                strcat(replaced_command, shell_pid_str);
                replaced_command_length += strlen(shell_pid_str);
            } else {
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

alias_command = get_alias(replaced_command);
if (alias_command != NULL) {
    execute_command(alias_command, path);
    return;
}

token = my_strtok(replaced_command, " \t\n");
while (token != NULL && arg_count < MAX_ARGS - 1) {
    args[arg_count] = token;
    arg_count++;
    token = my_strtok(NULL, " \t\n");
}
args[arg_count] = NULL;

if (arg_count == 0) {
    return;
}

if (strcmp(args[0], "exit") == 0) {
    exit_shell();
    return;
} else if (strcmp(args[0], "cd") == 0) {
    execute_cd(args);
    return;
} else if (strcmp(args[0], "setenv") == 0) {
    execute_setenv(args);
    return;
} else if (strcmp(args[0], "unsetenv") == 0) {
    execute_unsetenv(args);
    return;
}

execute_external_command(args, path);
}