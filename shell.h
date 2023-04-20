#ifndef SHELL_H
#define SHELL_H

// standard library headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

// maximum number of arguments for a command
#define MAX_ARGS 64

// declaration of the 'environ' variable
extern char **environ;



#endif /* SHELL_H */

