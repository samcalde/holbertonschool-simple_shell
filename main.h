#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
int checkdir(char **str);
int forkshell(char *file, char **str, char *env);
int printenv(char *line);

#endif
