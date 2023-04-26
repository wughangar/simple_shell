#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


/**
 * main - unix command line interpreter
 * @arg: pointer to arguments to find path for
 * @path: pointer to path
 *
 * Return: pointer to the full path
 */

char *find_path(char *arg, char *path);
int my_strcmp(const char *s1, const char *s2);

int main(int argc, char **argv, char **envp)
{
	char *args[1024];
	char *temp = NULL;
	char *commands = NULL;
	char *cpath = NULL;
	char *tok = NULL;
	size_t len = 0;
	pid_t pid;
	int i = 0;
	int j = 0;
	FILE *fp;

	if (argc > 1)
	{
		for (i = 1; i < argc && i < 1023; i++)
		{
			args[i - 1] = argv[i];
		}
		args[1 - 1] = NULL;
	}
		temp = (char *)malloc(len + 1);
		if (temp == NULL)
		{
			perror("memory allocation error");
			exit(1);
		}

	while (1)
	{
	printf("$ ");

	if (getline(&temp, &len, stdin) == -1)
		break;

	temp[strcspn(temp, "\n")] = '\0';


	if (my_strcmp(temp, "exit") == 0)

		break;

	if (my_strcmp(temp, "env") == 0)
	{

		for (j = 0; envp[j] != NULL; j++)
			printf("%s\n", envp[j]);
	continue;
	}

	commands =  strtok(temp, ";");

	while (commands != NULL)
	{
	tok = strtok(commands, " ");
	i = 0;
	while (tok != NULL && i < 1023)
	{
		args[i++] = tok;
		tok = strtok(NULL, " ");
	}
	args[i] = NULL;

	if (i > 0 && strcmp(args[i - 1], "-") == 0 && i < 1023)
	{
		args[i - 1] = NULL;
		fp = freopen(args[i - 2], "r", stdin);
		if (fp == NULL)
		{
			printf("Error opening file\n");
			continue;
		}
	}

	cpath = getenv("PATH");
	cpath = find_path(args[0], cpath);

	if (cpath == NULL)
	{
		printf("%s: command not found\n", args[0]);
		commands = strtok(NULL, ";");
		continue;
	}

	pid = fork();
	if (pid == 0)
		execve(cpath, args, envp);
	else
		wait(NULL);
	commands = strtok(NULL, ";");
	}
}
	free(temp);
	return (0);
}
int my_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(const unsigned char *)s1 - *(const unsigned char *)s2);
}

/**
 * find_path - finds the path
 * @arg: pointer arguments
 * @path: pointer to path
 *
 * Return: path
 */

char *find_path(char *arg, char *path)
{
	char *fpath = NULL;
	char *dir = NULL;
	char *pcopy = NULL;

	pcopy = strdup(path);
	if (pcopy == NULL)
	{
		exit(1);
	}

	dir = strtok(pcopy, ":");
	fpath = malloc(strlen(dir) + strlen(arg) + 2);
	while (dir != NULL)
	{
		if (fpath == NULL)
		{
			exit(1);
		}

		sprintf(fpath, "%s/%s", dir, arg);

		if (access(fpath, F_OK) == 0)
		{
			free(pcopy);
			return (fpath);
		}

		dir = strtok(NULL, ":");
	}
	free(fpath);
	free(pcopy);
	return (NULL);
}
