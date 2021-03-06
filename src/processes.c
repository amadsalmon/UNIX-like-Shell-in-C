#include "../include/processes.h"

int push_pid(pid_list * head, pid_t pid) {
    if (pid == -1)
    {
        return 0;
    }

    pid_list * current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    /* Add the new pid */
    current->next = (pid_list *) malloc(sizeof(pid_list));
    current->next->pid = pid;
    current->next->next = NULL;

    return 1;
}

struct process * create_process(char **words){
    struct process *p = (struct process *) malloc(sizeof(struct process));
    p->argv = words;
    /* 1) Déterminer si words[0] builtin ou external */
    /* 2) Parcourir words et chercher redirection */
    /* 3) Remplir p */

    if (is_builtin(words))
    {
        p->type = BUILTIN_COMMAND;
        p->path = words[0];
    }
    else
    {
        p->type = EXTERNAL_COMMAND;

        char *path = malloc(5 + strlen(words[0]));
        strcat(path, "/bin/");
        strcat(path, words[0]);
        p->path = path;

        int i = 0;
        while (words[i] != NULL)
        {
            if (words[i][0] == '>') {
                p->output_flag = O_CREAT | O_WRONLY;
                p->output = words[i+1];
                if (words[i + 1] != NULL && words[i + 1][0] == '>')
                {
                    p->output = words[i+2];
                    p->output_flag |= O_APPEND;
                }                
                words[i] = NULL;
                break;
            } else if (words[i][0] == '<'){
                p->output_flag = O_RDONLY;
                p->input = words[i+1];
                words[i] = NULL;
                break;
            } else {
                i++;
            }
        }
    }

    return p;
}

int run_process(pid_list* current, char** envp, int in_fd, int out_fd){
    struct process *p = current->p;

    if (p == NULL){
        return 0;
    }

    pid_t pid;
    pid = fork();

    if (pid < 0)
    {
        // Error forking
        perror("PID forking failed.");
        exit(-1);
    }
    else if (pid == 0)
    {
        if(in_fd != STDIN_FILENO){
            dup2(in_fd, STDIN_FILENO);
            close(in_fd);
        }

        if(out_fd != STDOUT_FILENO){
            dup2(out_fd, STDOUT_FILENO);
            close(out_fd);
        }

        execve(p->path, p->argv, envp);
        printf("Error: execve %s\n", p->path);
        exit(-1);
    }
    else
    {
        current->pid = pid;
    }

    return 1;
}

/* Function to delete the entire linked list */
int zombies_cleanup(pid_list* head)  
{  
    pid_list* current = head;  
    pid_list* next;  
  
    while (current != NULL)  
    {  
        next = current->next;  

        int uncleaned_zombie = 1;
        int deadID, status = 0;
        while(uncleaned_zombie) {
            deadID = waitpid(-1, &status, WNOHANG);
            if(WIFEXITED(status)) {
                free(current);  
                current = next;
            }
            else if (deadID == 0)
            {
                uncleaned_zombie = 0;
            }
            else
            {
                return 0;
            }
        }
         
    }  
      
    /* Dereference head to affect the real head back in the caller. */
    head = NULL;

    return 1;
}

int launch_external_command(char** args, char**envp, pid_list * pidlist){
    pid_t pid;
    int status;

    pid = fork();
    push_pid(pidlist, pid);
    
    if (pid < 0)
    {
        // Error forking
        perror("PID forking failed.");
        exit(-1);
    }
    else if (pid == 0)
    {
        // Child process

        
         
        char * path = find_path(envp, args[0]);
        if (execve(path, args, envp) == -1)
        {
            perror("Execve error");
        }
        //exit(EXIT_FAILURE);
    }
    else
    {
        // Parent process
        pid = wait(&status);
        if (pid==-1) {
            perror("waitpid: "); 
            exit(-1);
        }
    }
    return 0;
}