#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

/**
 * main - unix command line interpreter
 * @arg: pointer to arguments to find path for
 * @path: pointer to path
 *
 * Return: pointer to the full path
 */

int f_env(char *arg);
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
	FILE *fp;
	char *path;
	char *new_path;
	char *prompt = "$ ";

	path = getenv("PATH");
	new_path = malloc(strlen(path) + strlen("/sbin") + 2);
	sprintf(new_path, "%s:/bin", path);
	setenv("PATH", new_path, 1);
	free(new_path);

	execve("/bin/sh", argv, envp);

	perror("execve");

	if (argc > 1)
	{
		for (i = 1; i < argc && i < 1023; i++)
		{
			args[i - 1] = argv[i];
		}
		args[i - 1] = NULL;
	}

	temp = (char *)malloc(len + 1);
	if (temp == NULL)
	{
		perror("memory allocation error");
		exit(1);
	}

	while (1)
	{
		printf("%s ", prompt);

		if (getline(&temp, &len, stdin) == -1)
		{
			printf("\n");
			break;
		}
		temp[strcspn(temp, "\n")] = '\0';

		if (my_strcmp(temp, "\n") == 0)
			continue;

		if (my_strcmp(temp, "exit") == 0)
			break;

		if (f_env("env") == 0)
		{
			printf("Env found\n");
		}
		else
		{
			printf("enviroment variable not found\n");
		}

		commands = strtok(temp, ":");

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

			if (i > 0 && my_strcmp(args[i - 1], "-") == 0 && i < 1023)
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
			{
				if (execve(cpath, args, envp) == -1)
				{
					perror("execve failed");
					exit(EXIT_FAILURE);
				}
			}
			else if (pid < 0)
			{
				perror("fork failed");
			}
			else
			{
				wait(NULL);
			}

			commands = strtok(NULL, ";");
		}
	}
	free(temp);
	return (0);
}

/**
 * my_strcmp - comapres strings
 * @s1: pointer to first string
 * @s2: pointer to second string
 *
 * Return: 0
 */
int my_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	if (*s1 == '\0' && *s2 == '\0')
	{
		return (0);
	}
	return (*(const unsigned char *)s1 - *(const unsigned char *)s2);
}
/**
 * _strdup - duplicates a string
 * @str: string to be dupliated
 * Return: string
 */
char *_strdup(char *str)
{
	int len = 0;
	char *nstr;
	int i;

	if (!str)
		return (NULL);
	while (str[len])
		len++;

	nstr = malloc(sizeof(char) * (len + 1));

	if (!nstr)
		return (NULL);

	for (i = 0; i < len; i++)
		nstr[i] = str[i];

	nstr[len] = '\0';

	return (nstr);
}

char *_strdup(char *str);
/**
 * find_path - fids a path
 * @arg: pointer to argument passed
 * @path: pointer to the path
 * Return: pointer to path found
 */
char *find_path(char *arg, char *path)
{
	char *fpath = NULL;
	char *dir = NULL;
	char *pcopy = NULL;

	pcopy = _strdup(path);
	if (pcopy == NULL)
	{
		perror("strdup failed");
		exit(1);
	}

	dir = strtok(pcopy, ":");
	while (dir != NULL)
	{
		fpath = malloc(strlen(dir) + strlen(arg) + 2);
		if (fpath == NULL)
		{
			perror("malloc failed");
			exit(1);
		}

		sprintf(fpath, "%s/%s", dir, arg);

		if (access(fpath, F_OK | X_OK) == 0)
		{
			free(pcopy);
			return (fpath);
		}

		free(fpath);
		dir = strtok(NULL, ":");
	}
	free(pcopy);
	fprintf(stderr, "%s: command not found\n", arg);
	exit(1);
}
extern char **environ;
/**
 * f_env - sets env variables
 * @arg: pointer to arg
 * Return: int
 */
int f_env(__attribute__((unused))char *arg)
{
	char *evar;
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		evar = environ[i];
		printf("%s\n", evar);
	}
	return (1);
}
