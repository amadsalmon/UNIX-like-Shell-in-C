#include "../include/builtins.h"

typedef int (*builtin_function)(char **args, char **envp);
builtin_function builtin_functions[4] = {cd, pwd, print, set};
char *builtin_str[] = {"cd", "pwd", "print", "set"};


int run_builtin(char** args, char**envp){
    if (args[0] == NULL)
        perror("Error: please enter a command.");
    for (int i = 0; i < nb_builtins(); i++)
    {
        if (strcmp(args[0], builtin_str[i]) == 0){
            return (*builtin_functions[i])(args, envp);
        }
    }
    return 0;
}

int nb_builtins(){
    return sizeof(builtin_str) / sizeof(builtin_str[0]);
}

int cd(char **args, char**envp)
{
    if (args[1] == NULL) {
        fprintf(stderr, "cd: expected argument\n");
        return 0;
    }
    if (chdir(args[1]) == 0) {
        return 1;
    } else
    {
        perror("Error: can't change directory.");
        return 1;
    }
}

int pwd(char **args, char**envp)
{
    if (args[1] != NULL) {
        fprintf(stderr, "pwd: unexpected argument\n");
        return 0;
    }

    // Loop on all the environment variables until PWD is found.
    char* pwd = NULL;
    char tmp[4]; // 4 is the size of 'PWD\0'
    for (int i = 0; envp[i] != NULL; i++)
    {
        substr(tmp, envp[i], 0, 3);
        if (strcmp(tmp, "PWD") == 0)
        {
            pwd = envp[i]+4; // ignore 'PWD=' which length is 4.
            printf("%s", pwd);
            return 1;
        }
    }
    return 0;
}

int print(char **args, char**envp)
{
    for(int i = 0; envp[i]!=NULL; i++){
        printf("%s\n", envp[i]);
    }
    return 1;
}

int set(char **args, char**envp) 
{
    // TODO: check no special character ( ' ', '\t', '<', '>', '|', '', '=') can make the shell crash.
    return 0;
}