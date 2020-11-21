#include <stdio.h>
// #include <stddef.h>
// #include <stdlib.h>
// #include <errno.h>
// #include <limits.h>
// #include <string.h>
// #include <unistd.h>

#include "../include/processes.h"
#include "../include/builtins.h"

int main(int argc, char** argv, char**envp) {

    for (int i=0;envp[i]!=NULL;i++){
        printf("env[%d]=%s\n",i,envp[i]);
    }
    printf("\n");

    // set stdout without buffering so what is printed
    // is printed immediately on the screen.
    // setvbuf(stdout, NULL, _IONBF, 0);
    // setbuf(stdout, NULL);

    while(1) {
        printf("> ");
        fflush(stdout);
        char* line = readline();
        printf("%s\n", line);
        char** words = split_in_words(line);
        for (int i=0;words[i]!=NULL;i++){
            printf("[%s], ", words[i]);
        }

        run_builtin(words, envp);

        printf("\n");
        free(words);
        free(line);
    }
    return 0;
}