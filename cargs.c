#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
/**
 * main - gets the input
 *
 * Return: o
 */

char *find_path(char *arg, char *path)
{
	char *fpath = NULL;
	char *dir = strtok(path, ":");
	while (dir != NULL)
	{
		fpath = malloc(strlen(dir) + strlen(arg) + 2);
		sprintf(fpath, "%s/%s", dir, arg);
		if (access(fpath, X_OK) == 0)
		{
			return (fpath);
		}
		free(fpath);
		dir = strtok(NULL, ":");
	}
	return (NULL);
}
int main(void)
{
	char *temp = NULL;
	size_t len = 0;
	pid_t pid;
	ssize_t read;

	while(1)
	{
		printf("$ ");
		read = getline(&temp, &len, stdin);

		if (read == -1)
		{
			printf("\n");
			break;
		}

		temp[strcspn(temp, "\n")] = '\0';

		char *tok = strtok(temp, " ");
		char *args[1024];
		int i = 0;

		while (tok != NULL)
		{
			args[i++] = tok;
			tok = strtok(NULL, " ");
		}
		args[i] = NULL;

		char *cpath = find_path(args[0], cpath);

		if (cpath != NULL)
		{
			pid = fork();
			if (pid == 0)
			{
				execve(cpath, args, NULL);
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
				printf("%s: no such command or directory found\n", args[0]);
			}
		}
		free(temp);

		return (0);
}
