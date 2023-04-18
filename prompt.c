#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include "main.h"

/**
 * run_shell- gets command and executes it
 *
 * Return: 0
 */

int run_shell(void)
{
	char *temp = NULL;
	size_t len = 0;
	pid_t pid;
	ssize_t read;

	while (1)
	{
		printf("$ ");
		read = getline(&temp, &len, stdin);

		if (read == -1)
		{
			printf("\n");
			break;
		}

		temp[strcspn(temp, "\n")] = 0;

		char *args[] = {temp, NULL};

		if (access(temp, X_OK) == 0)
		{
			pid = fork();
			if (pid == 0)
			{
				execve(temp, args, NULL);
				perror("execve process failed");
				exit(EXIT_FAILURE);
			}
			else if (pid < 0)
			{
				perror("fork process failed");
			}
			else
			{
				waitpid(pid, NULL, 0);
			}
		}
			else
			{
				printf("%s: no such file or directory\n", temp);
			}
		}
		free(temp);

		return (0);
}
