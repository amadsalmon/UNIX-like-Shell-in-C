#include <stdio.h>
#include <unistd.h>

#include "processes.h"
#include "helpers.h"

#define READEND 0
#define WRITEEND 1

int pipeline_manager(char **words, char **envp, pid_list *pidlist);