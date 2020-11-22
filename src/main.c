#include <stdio.h>
// #include <stddef.h>
// #include <stdlib.h>
// #include <errno.h>
// #include <limits.h>
// #include <string.h>
// #include <unistd.h>

#include "../include/builtins.h"
#include "../include/pipes.h"

int main(int argc, char** argv, char**envp) {

    pid_list *pidlist ;

    for (int i=0; envp[i]!=NULL; i++){
        printf("env[%d]=%s\n",i,envp[i]);
    }
    printf("\n");

    // set stdout without buffering so what is printed
    // is printed immediately on the screen.
    // setvbuf(stdout, NULL, _IONBF, 0);
    // setbuf(stdout, NULL);

    while(1) {
        pidlist = (pid_list *) malloc(sizeof(pid_list));

        printf("> ");
        fflush(stdout);
        char* line = readline();
        printf("%s\n", line);
        char** words = split_in_words(line);
        for (int i=0;words[i]!=NULL;i++){
            printf("[%s], ", words[i]);
        }

    
        

        // Check if given command is made of pipes.
        if(is_pipeline(words) != -1){
            pipeline_manager(words, envp, pidlist);
        }
        // Check if wanted command is implemented by the built-in functions.
        if (run_builtin(words, envp))
        {
        }
        // If not, launch the command as an external command.
        else 
        {
            launch_process(words, envp, pidlist);
        }

        printf("\n");
        free(words);
        free(line);
    }
    return 0;
}