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

char *find_path(char *arg, char *path);

int main(__attribute__((unused))int ac, __attribute__((unused))char **av, char **envp)
{
	char *temp, *args[1024], *cpath;
	size_t len = 0;
	pid_t pid;
	char *tok;
	int i = 0;
	char **j;
	temp = (char *) malloc(len + 1);
	if (temp == NULL)
		exit(1);

	while (1)
	{	
	printf("$ ");
	
	if (getline(&temp, &len, stdin) == -1)
		break;
	

	temp[strcspn(temp, "\n")] = '\0';

	if(strcmp(temp, "exit") == 0)
	{
		break;
	}

	if (strcmp(temp, "env") == 0)
	{
		for (j = envp; *j != NULL; j++)
			printf("%s\n", *j);
		continue;
	}

	tok = strtok(temp, " ");
	while (tok != NULL && i < 1023)
	{
		args[i++] = tok;
		tok = strtok(NULL, " ");
	}
	args[i] = NULL;

	cpath = getenv("PATH");
	cpath = find_path(args[0], cpath);

	if (cpath == NULL)
	{
		printf("%s: command not found\n", args[0]);
		continue;
	}

	pid = fork();
	if (pid == 0)
		execve(cpath, args, (char* const*) envp);
	else
		wait(NULL);
	}
	free(temp);
	return(0);
}


char *find_path(char *arg, char *path)
{
	char *fpath = NULL;
	char *dir = strtok(path, ":");

	while (dir != NULL)
	{
		fpath = (char *) malloc(strlen(dir) +strlen(arg) + 2);
		if (fpath == NULL)
			exit(1);
		sprintf(fpath, "%s/%s", dir, arg);
		if (access(fpath, F_OK) == 0)
			return (fpath);
		free(fpath);
		fpath = NULL;
		dir = strtok(NULL, ":");
	}
	return (NULL);
}
