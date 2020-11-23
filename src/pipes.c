#include "../include/pipes.h"

int pipeline_manager(char** words, char** envp, pid_list * pidlist)
{
    int fd[2];
    int in_fd, out_fd;

    pid_list *current = pidlist;
    
    int i_pipe;
    while (words[0] != NULL)
    {
        if((i_pipe = is_pipeline(words)) != -1)
        {
            words[i_pipe] = NULL;
        }

        int length = 0;
        while (words[length]!=NULL)
        {
            length++;
        }

        struct process *p = create_process(words);
        pidlist->p = p;

        if (current->p == NULL)
        {
            current->p = p;
        }
        else
        {
            current->next = malloc(sizeof(pid_list));
            current->next->p = p;
            current = current->next;
        }

        if (i_pipe == -1)
        {
            length--;
        }

        words += length + 1;
    }
    current = pidlist;

    while (current != NULL)
    {
        if (current == pidlist)
        {
            if (current->p->input != NULL)
            {
                in_fd = open(current->p->input, O_RDONLY);
                if (in_fd < 0)
                {
                    perror("Error: open in pipe_manager();\n");
                    in_fd = STDIN_FILENO;
                }
            }
        }
        else if (current->next != NULL)
        {
            pipe(fd);
            out_fd = fd[WRITEEND];
            run_process(current, envp, in_fd, out_fd);
            in_fd = fd[READEND];
            close(out_fd);
        }
        else if (current->next == NULL)
        {
            out_fd = open(current->p->output, current->p->output_flag, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
            if (out_fd < 0)
            {
                perror("Error: open in pipe_manager();\n");
                out_fd = STDOUT_FILENO;
            }
            run_process(current, envp, in_fd, out_fd);
        }

        current = current->next;
    }

    /* Zombie cleaning */
    current = pidlist;
    pid_list *tmp;
    int status;
    while (current != NULL)
    {
        
        do 
        {
            waitpid(current->pid, &status, 0);
        } while (!WIFEXITED(status));

        tmp = current;
        current = current->next;
        free(tmp);
    }
    return 0;
}
