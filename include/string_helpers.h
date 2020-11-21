#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Read a line from standard input into a newly allocated 
 * array of char. The allocation is via malloc(size_t), the array must be freed via free(void*).
 */
char *readline(void);

/* 
 * Split the string in words, according to the simple shell grammar.
 * Returns a null-terminated array of words.
 * The array has been allocated by malloc, it must be freed by free.
 */
char **split_in_words(char *line);

/**
 * Function to implement substring function in C.
 * Extracts length characters from source string starting from pos index, then copies them into the destination string.
 * */
char *substr(char *destination, char *source, int pos, int length);