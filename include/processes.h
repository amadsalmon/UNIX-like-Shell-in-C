#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "builtins.h"

#define BUILTIN_COMMAND 0
#define EXTERNAL_COMMAND 1

struct process
{
    int type;
    char *path;
    int argc;
    char **argv;
    char *input;
    char *output;
    int output_mode;
};

typedef struct pid_node
{
    pid_t pid;
    struct process *p;
    struct pid_node *next;
} pid_list;

push_pid(pid_list *head, pid_t pid);

struct process *create_process(char **words);

int run_process(struct process *p, char **envp, int in_fd, int out_fd);

int launch_process(char **args, char **envp, pid_list *pidlist);

int zombies_cleanup(pid_list *head);
