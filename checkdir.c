#include "main.h"

/**
* checkdir - check directories to find executable file
* @str: tokenized input line
*
* Return: 0
*/

int checkdir(char **str)
{
	char *var[128], *command, temp[128], *env = malloc(1024);
	int i = 1;
	const char delimiter[] = ":";
	struct stat file_stat;

	strcpy(env, getenv("PATH"));
	if (env == NULL)
		return (0);
	var[0] = strtok(env, delimiter);
	while (1)
	{
		var[i] = strtok(NULL, delimiter);
		if (var[i] == NULL)
			break;
		i++;
	}
	if (stat(str[0], &file_stat) == 0)
		return (forkshell(str[0], str, env));
	command = malloc(32);
	if (command == NULL)
		return (0);
	strcpy(command, "/");
	strcat(command, str[0]);
	for (i = 0; var[i] != NULL; i++)
	{
		strcpy(temp, var[i]);
		strcat(temp, command);
		if (stat(temp, &file_stat) == 0)
		{
			free(command);
			return (forkshell(temp, str, env));
		}
	}
	fprintf(stderr, "./hsh: 1: %s: not found\n", str[0]);
	free(env);
	free(command);
	return (0);
}

/**
* forkshell - when command is found, it creates the fork
* @file: location of the executable file
* @env: memory to free
* @str: arguments
*
* Return: 0
*/
int forkshell(char *file, char **str, char *env)
{
	pid_t pid;
	int status;
	char **envp = environ;

	pid = fork();
	if (pid == -1)
	{
		exit(1);
	}
	else if (pid == 0)
	{
		if (execve(file, str, envp) == -1)
		{
			perror("execve");
			return(127);
		}
	}
	else
	{
		wait(&status);
		free(env);
	}
	return (0);
}

/**
* printenv - prints environment
* @line: bring file to free and save space in main
* Return: 0 on success
*/
int printenv(char *line)
{
	char **env = environ;

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
	free(line);
	return (0);
}
