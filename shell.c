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
	char *line = NULL;
	char *token;
	const char delimiter[] = " \n\t";
	char *str[5];
	int i = 1;

	while (1)
	{
		line = NULL;
		i = 1;
		if (isatty(STDIN_FILENO))
			write(1, "($) ", 5);
		line_len = getline(&line, &arg_line_len, stdin);
		if (line_len == EOF || (strcmp(line, "exit\n") == 0))
			exit(0);
		token = strtok(line, delimiter);
		str[0] = token;
		if (token != NULL)
		{
			while (token != NULL)
			{
				token = strtok(NULL, delimiter);
				str[i] = token;
				i++;
			}
			str[i] = NULL;
			free(line);
			checkdir(str);
		}
	}
	return (0);
}
