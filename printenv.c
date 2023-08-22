#include "main.h"

extern char **environ;

int printenv() 
{
    char **env = environ;

    while (*env != NULL) {
        printf("%s\n", *env);
        env++; 
    }

    return (0);
}
