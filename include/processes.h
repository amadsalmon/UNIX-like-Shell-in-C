#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "builtins.h"
#include "helpers.h"

#define BUILTIN_COMMAND 0
#define EXTERNAL_COMMAND 1

struct process
{
    int type;
    char *path;
    char **argv;
    char *input;
    char *output;
    int output_flag;
};

typedef struct pid_node
{
    pid_t pid;
    struct process *p;
    struct pid_node *next;
} pid_list;

int push_pid(pid_list *head, pid_t pid);

struct process *create_process(char **words);

int run_process(pid_list *current, char **envp, int in_fd, int out_fd);

int launch_external_command(char **args, char **envp, pid_list *pidlist);

int zombies_cleanup(pid_list *head);
