#include "main.h"

extern char **environ;

int printenv(char *line) 
{
    char **env = environ;

	free(line);
    while (*env != NULL) {
        printf("%s\n", *env);
        env++; 
    }

    return (0);
}
