# UNIX-like Shell in C

Amad Salmon - November 2020

## Purpose

In this project, we plan to build an interpreter for a simplified command language, commonly referred to as "shell".  
The goal is on the one hand to understand the structure of such an interpreter and on the other hand to learn how to use some important system calls, typically those concerning process management, pipes, and redefinition of standard input and output files.

## Features

### Simple internal commands

Internal commands are implemented by the interpreter code. We will cover only a few of them :

- **cd :** _(change directory)_ command used to change the current working directory.
- **pwd :** _(print working directory)_ writes the full pathname of the current working directory to the standard output.
- **print :** prints all the environment variables.
- **set :** used to set a specific environment variable to a certain value. 

### External commands

When a command is not implemented by the built-in functions of the interpreter, it will launch them externally via `fork` and `execve`.
This allows the interpreter to magnificently run commands such as `ls -al` or even `vim` for example, which is quite impressive to be honest.  
![Launching ls -al on the interpreter](https://image.noelshack.com/fichiers/2020/48/1/1606096102-ls-al.png "Screenshot")

### Background commands _(incoming)_

A command can be launched to run in the background:
`ls &`

### Pipelines

This is about redirecting standard inputs and outputs (stdin and stdout).  
For instance, the command below is made of three piped commands:

```
> cat /etc/passwd | grep root ls -a ~ | grep .bash
```

### Redirection Operators

This is about redirecting standard inputs and outputs _(stdin and stdout)_ just like in the commands below.

```
> ls -al > foo
> cat foo >> bar
```

## To compile:

```
make
```

## To run:

```
./main
```
