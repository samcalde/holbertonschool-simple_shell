#include "main.h"

extern char **environ;

int printenv(char *line)
{
    char **env = environ;

    while (*env != NULL) {
        printf("%s\n", *env);
        env++; 
    }

	free(line);
    return (0);
}
