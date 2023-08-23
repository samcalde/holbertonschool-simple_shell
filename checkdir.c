#include "main.h"

extern char **environ;

/**
 * checkdir - check directories to find executable file
 * @str: tokenized input line
 *
 * Return: 0
 */
int checkdir(char **str)
{
	char *var[128], *command, *temp;
	int i = 1;
	const char delimiter[] = ":"; /*salto linea no tenia sentido*/
	struct stat file_stat;
	char *env = malloc(1024); /**/

	if (env == NULL)
		return (0);
	strcpy(env, getenv("PATH"));
	var[0] = strtok(env, delimiter);
	while (1)
	{
		var[i] = strtok(NULL, delimiter);
		if (var[i] == NULL)
			break;
		i++;
	}
	if (stat(str[0], &file_stat) == 0)
	{
		forkshell(str[0], str, env);
		return (0);
	}
	command = malloc(32); 
	if (command == NULL)
		return (0);

	strcpy(command, "/");
	strcat(command, str[0]);
	for (i = 0; var[i] != NULL; i++)
	{
		temp = var[i];
		strcat(temp, command);
		if (stat(temp, &file_stat) == 0) /*tener 2 stats no tiene sentido*/
		{
			free(command);
			forkshell(temp, str, env);
			return (0);
		}
	}
	free(env);
	free(command);
	return (0);
}

/**
 * forkshell - when command is found, it creates the fork
 * @fileloc: location of the executable file
 * @env: memory to free
 * @str: arguments
 *
 * Return: 0
 */
int forkshell(char *file, char **str, char *env)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		exit(1);
	}
	else if (pid == 0)
	{
		if (execve(file, str, environ) == -1)
		{
			perror("execve");
			exit(2);
		}
	}
	else
	{
		wait(&status);
		free(env);
	}
	return (0);
}

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
