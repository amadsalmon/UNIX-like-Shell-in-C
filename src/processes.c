#include "../include/processes.h"

int launch_process(char** args, char**envp){
    pid_t pid;
    int status;

    pid = fork();
    if (pid < 0) {
        // Error forking
        perror("PID forking failed.");
        exit(-1);
    } else if (pid == 0) {
        // Child process

        char path[100] = "/bin/";
        strcat(path, args[0]);
        if (execve(path, args, envp) == -1)
        {
            perror("Execve error");
        }
        //exit(EXIT_FAILURE);
    } else {
        // Parent process
        pid = wait(&status);
        if (pid==-1) {
            perror("waitpid: "); 
            exit(-1);
        }
    }
    return 0;
}