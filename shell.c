#include "main.h"

int main()
{
    ssize_t line_len = 0;
    size_t arg_line_len = 0;
    char *line = NULL;
    char *token;
    const char delimiter[] = " ";
    pid_t pid;
    char *str[5];
    int i = 0;
	int status; //variable para wait

    while(1)
    {
        write(1, "($)", 4);
        line = malloc(1024 * sizeof(char)); //memoria para la línea de input
        if (line == NULL)
            exit(1);
        line_len = getline(&line, &arg_line_len, stdin);
        if (line_len == EOF)
        {
            free(line);
            exit(0);
        }
        token = strtok(line, delimiter); //corregido, faltaba ejecutar strtok
        while (token != NULL)
        {
            str[i] = token;
            token = strtok(NULL, delimiter);
            i++;
        }
        str[i] = NULL;
        pid = fork();
        if (pid == -1)
            exit (1);
        else if (pid == 0)
        {
            execve(str[0], str, NULL); //cuando leamos lo del pa
			perror("execve");
			exit(1);
        } // falta correr el wait, hacer ejercicios del concept page para entender
		else
			wait(&status);
    }
    return (0);
}