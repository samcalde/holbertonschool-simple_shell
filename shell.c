#include "main.h"
/**
* main - simple shell
*
* Return: 0 when exiting
*/

int main(void)
{
    ssize_t line_len = 0;
    size_t arg_line_len = 0;
    char *line = NULL, *token, *str[5];
    const char delimiter[] = " \n\t\0";
    int i = 1;
    while (1)
    {
        line = NULL;
        i = 1;
        if (isatty(STDIN_FILENO))
            write(1, "($) ", 5);
        line_len = getline(&line, &arg_line_len, stdin);
        if (line_len == EOF || (strcmp(line, "exit\n") == 0))
        {
            free(line);
            exit(0);
        }
        token = strtok(line, delimiter);
        str[0] = token;
        if (str[0] == NULL)
        {
            free(line);
            return(0);
        }
        if (strcmp(str[0], "env") == 0)
            printenv(line);
        else if (token != NULL)
        {
            while (token != NULL)
            {
                token = strtok(NULL, delimiter);
                if (token != NULL)
                {
                    str[i] = token;
                    i++;
                }
            }
            str[i] = NULL;
            checkdir(str);
            free(line);
        }
        else
            free(line);
    }
    return (0);
}