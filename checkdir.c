#include "main.h"

/**
 * checkdir - check directories to find executable file
 * @str: tokenized input line
 * @line: full line with allocated memory
 *
 * Return: 0
 */
int checkdir(char **str, char *line)
{
	char *var[128], *command, *temp;
	int i = 1;
	const char delimiter[] = ":\n";
	struct stat file_stat;
	char *env = malloc(1024);

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
	command = malloc(32); 
	if (command == NULL)
	{
		free(env);
		return (0);
	}
	if (stat(str[0], &file_stat) == 0)
	{
		forkshell(str[0], str, command, env);
		return (0);
	}
	strcpy(command, "/");
	strcat(command, str[0]);
	for (i = 0; var[i] != NULL; i++)
	{
		temp = var[i];
		strcat(temp, command);
		if (stat(temp, &file_stat) == 0)
		{
			forkshell(temp, str, command, env);
			return (0);
		}
	}
	return (0);
}

/**
 * forkshell - when command is found, it creates the fork
 * @file: location of the executable file
 * @str: arguments
 * @command: memory space to be freed
 * @env: memory space to be freed
 *
 * Return: 0
 */
int forkshell(char *file, char **str, char *command, char *env)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		freemem(command, env);
		exit(0);
	}
	else if (pid == 0)
	{
		freemem(command, env);
		if (execve(file, str, NULL) == -1)
		{
			perror("execve");
			exit(0);
		}
	}
	else
	{
		wait(&status);
		freemem(command, env);
	}
	return (0);
}

/**
 * freemem - free allocated memory
 * @command: memory space to be freed
 * @env: memory space to be freed
 *
 * Return: 0
 */
int freemem(char *command, char *env)
{
	free(command);
	free(env);
	return (0);
}
