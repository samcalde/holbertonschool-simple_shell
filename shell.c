#include "main.h"

int main()
{
    ssize_t line_len = 0;
    size_t arg_line_len = 0;
    char *line = NULL;
    char *token;
    const char delimiter[] = " \n\t";
    pid_t pid;
    char *str[5];
    int i = 1;
    int status;

    while(1)
    {
		line = NULL;
        i = 1;
		if (isatty(STDIN_FILENO))
        	write(1, "($) ", 5);
        line_len = getline(&line, &arg_line_len, stdin);
        if (line_len == EOF)
        {
            free(line);
            exit(0);
        }
        token = strtok(line, delimiter);
        str[0] = token;
        while (token != NULL)
        {
            token = strtok(NULL, delimiter);
            str[i] = token;
            i++;
        }
        str[i] = NULL;
        pid = fork();
        if (pid == -1)
		{
			free(line);
			exit(0);
		}
        else if (pid == 0)
        {
            free(line);
            if(execve(str[0], str, NULL) == -1)
            {
                perror("execve");
                exit(0);
            }
        }
        else
            wait(&status);
        free(line);
    }
    return (0);
}
