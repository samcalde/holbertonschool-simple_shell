#include "main.h"

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
		if (stat(temp, &file_stat) == 0)
		{
			free(command);
			forkshell(temp, str, env);
			return (0);
		}
	}
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

	printf("file location before fork: %s\n", file);
	pid = fork();
	if (pid == -1)
	{
		exit(0);
	}
	else if (pid == 0)
	{
		free(env);
		printf("file location after fork: %s\n", file);
		if (execve(file, str, NULL) == -1)
		{
			perror("execve");
			exit(0);
		}
	}
	else
	{
		wait(&status);
		free(env);
	}
	return (0);
}
