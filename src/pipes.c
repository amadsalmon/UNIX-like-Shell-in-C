#include "../include/pipes.h"

int pipeline_manager(char** words, char** envp, pid_list * pidlist)
{
    int fd[2];
    pid_t pid;

    pipe(fd);

    int i_pipe = is_pipeline(words);
    while (i_pipe != -1)
    {
        words[i_pipe] = NULL;
        struct process * p = create_process(words);

        run_process(p, envp, -1, -1);
    }
}
