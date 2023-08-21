#include "main.h"

extern char **environ;

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
    for (i = 1; i < 15; i++)
	{
		var[i] = strtok(NULL, delimiter);
		if (var[i] == NULL)
			break;
	}

	command = malloc(128);
	if (command == NULL)
		return (0);

	if (stat(str[0], &file_stat) == 0)
		forkshell(str[0], str, line, command);

	strcpy(command, "/");
	strcat(command, str[0]);

	for (i = 0; var[i] != NULL; i++)
	{
		temp = var[i];
		strcat(temp, command);
		if (stat(temp, &file_stat) == 0)
		{
			forkshell(temp, str, line, command);
			break;
		}
    }
	return (0);
}

int forkshell(char *file, char **str, char *line, char *command)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		free(command);
		free(line);
		exit(0);
	}
	else if (pid == 0)
	{
		free(command);
		free(line);
		if(execve(file, str, NULL) == -1)
		{
			perror("execve");
			exit(0);
		}
	}
	else
	{
		wait(&status);
		free(command);
	}
	return (0);
}
