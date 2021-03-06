#ifndef __BUILTINS_H__
#define __BUILTINS_H__

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "helpers.h"

int run_builtin(char **args, char **envp);

/**
 * @returns 1 if given expression contains a function
 * */
int is_builtin(char **args);

int nb_builtins();

int cd(char **args, char **envp);

int pwd(char **args, char **envp);

int print(char **args, char **envp);

int set(char **args, char **envp);

#endif
