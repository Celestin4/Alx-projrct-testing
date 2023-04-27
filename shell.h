#ifndef SHELL_H
#define SHELL_H

/* standard library headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

/* maximum number of arguments for a command */
#define MAX_ARGS 512
#define MAX_COMMAND_LENGTH 1024
/* declaration of the 'environ' variable */
extern char **environ;

/* function declarations */
char *my_strtok(char *str, const char *delim);
int custom_getline(char **lineptr, size_t *n, FILE *stream);
void exit_shell();
void execute_cd(char **args, int arg_count);
void execute_external_command(char **args, char *path);
void execute_command(char *command, char *path);
void execute_external_command(char **args, char *path);
void execute_cd(char **args, int arg_count);
void execute_setenv(char **args, int arg_count);
void execute_unsetenv(char **args, int arg_count);
void execute_alias(char **args, int arg_count);
void add_alias(char *alias, char *command);
char *get_alias(char *alias);

#endif /* SHELL_H */
