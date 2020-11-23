#include "../include/helpers.h"

char *readline(void)
{
#define BUFFER_LENGTH 256
    static char buffer[BUFFER_LENGTH];
    int offset = 0;
    for (;;)
    {
        char c = fgetc(stdin);
        if (c == EOF)
        {
            printf("PANIC: EOF on stdin\n");
            exit(-1);
        }
        if (c == '\n')
            break;
        buffer[offset++] = c;
    }
    buffer[offset++] = '\0';
    char *line = malloc(offset);
    strcpy(line, buffer);
    return line;
}

char **split_in_words(char *line)
{
#define MAX_NWORDS 256
    static char *words[MAX_NWORDS];
    int nwords = 0;
    char *cur = line;
    char c;
    words[0] = NULL;
    while ((c = *cur) != 0)
    {
        char *word = NULL;
        char *start;
        switch (c)
        {
        case ' ':
        case '\t':
            /* Ignore any whitespace */
            cur++;
            break;
        case '<':
            word = "<";
            cur++;
            break;
        case '>':
            word = ">";
            cur++;
            break;
        case '|':
            word = "|";
            cur++;
            break;
        case ';':
            word = ";";
            cur++;
            break;
        case '&':
            word = "&";
            cur++;
            break;
        default:
            /* Another word */
            start = cur;
            if (c == '"')
            {
                c = *++cur;
                while (c != '"')
                    c = *++cur;
                cur++;
            }
            else
            {
                while (c)
                {
                    c = *++cur;
                    switch (c)
                    {
                    case 0:
                    case ' ':
                    case '\t':
                    case '<':
                    case '>':
                    case '|':
                    case ';':
                    case '&':
                        c = 0;
                        break;
                    default:;
                    }
                }
            }
            word = malloc((cur - start + 1) * sizeof(char));
            strncpy(word, start, cur - start);
            word[cur - start] = 0;
        }
        if (word)
        {
            words[nwords++] = word;
            words[nwords] = NULL;
        }
    }
    size_t size = (nwords + 1) * sizeof(char *);
    char **tmp = malloc(size);
    memcpy(tmp, words, size);
    return tmp;
}

char *substr(char *destination, char *source, int pos, int length)
{
    while (length > 0)
    {
        *destination = *(source + pos);
        destination++;
        source++;
        length--;
    }

    // End of string terminates destination string.
    *destination = '\0';

    // Return the destination string.
    return destination;
}

/**
 * Read an environment variable and returns its name.
 * The returned array must be freed.
 * 
 * @author Elias El Yandouzi (https://github.com/EliasEly)
 * */
char *name_envp(char *s) {
    int j;
    for (j = 0; s[j] != '='; j++);

    char *envp_name = malloc(j + 1 * sizeof(char));
    memcpy(envp_name, s, j);
    envp_name[j] = '\0';

    return envp_name;
}

void special_chars_remover(char *s)
{
    char *c = s;
    char *ch;

    while (*c != '\0') {
        switch (*c) {
        case ' ':
        case '\t':
        case '<':
        case '>':
        case '|':
        case '"':
        case '=':
            ch = c;
            // Delete the special character and 
            while (*ch != '\0') {
                *ch = *(ch + 1);
                ch++;
            }
            break;
        }
        c++;
    }
    return;
}

int number_of_args(char **args){
    int i;
    for (i = 0; args[i] != NULL; i++)
        ;
    return i;
}
