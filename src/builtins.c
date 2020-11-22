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
    int flag = 1;

    int nb_args = number_of_args(args);

    if (nb_args != 2){
        printf("Error: invalid number of arguments for set.\n");
        return 0;
    }

    // Remove any special character ( ' ', '\t', '<', '>', '|', '', '=') that can make the shell crash.
    special_chars_remover(args[1]);

    int i;
    for (int i = 0; envp[i] != NULL; i++)
    {
        char* name = name_envp(envp[i]);
        flag = strcmp(args[0], name);

        if (flag == 0){
            envp[i] = realloc(envp[i], 1 + strlen(name) + strlen(args[1]));
            strcpy(envp[i], name);
            strcat(envp[i], "=");
            strcat(envp[i], args[1]);
            free(name);
            return;
        }
        free(name);
    }

    envp = realloc(envp, (i+1) * sizeof(*envp));
    envp[i] = malloc(strlen(args[1]) * sizeof(char));

    strcpy(envp[i], args[0]);
    strcat(envp[i], "=");
    strcat(envp[i], args[1]);
    envp[i+1] =  NULL;

    return 0;
}