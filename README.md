# C UNIX-like Shell
*Amad Salmon - November 2020*

## Purpose
In this project, we plan to build an interpreter for a simplified command language, commonly referred to as "shell".  
The goal is on the one hand to understand the structure of such an interpreter and on the other hand to learn how to use some important system calls, typically those concerning process management, pipes, and redefinition of standard input and output files.

## Features
### Simple internal commands
Internal commands are implemented by the interpreter code. We will cover only a few of them :
* **cd :** *(change directory)* command used to change the current working directory.
* **pwd :**  *(print working directory)* writes the full pathname of the current working directory to the standard output.
* **print :** 
* **set :** 

### External commands
It is not about implementing these commands, but about launching them via `fork` and `execve`.

### Background commands *(incoming)*
A command can be launched to run in the background: 
`ls &`
### Pipelines
This is about redirecting standard inputs and outputs (stdin and stdout).  
For instance, the command below is made of three piped commands:
```
> cat /etc/passwd | grep root ls -a ~ | grep .bash
```

### Redirection Operators
This is about redirecting standard inputs and outputs *(stdin and stdout)* just like in the commands below.
```
> ls -al > foo  
> cat foo >> bar


## To compile:
gcc -g -o readline readline.c

## To run:
./readline
