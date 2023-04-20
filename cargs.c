#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
/**
 * find_path - gets the full path a command
 * @arg: pointer to the command
 * @path: pointer to the path
 * Return: pointer to the full path
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
                        return (fpath);
                free(fpath);
                dir = strtok(NULL, ":");
        }
        return (NULL);
}
/**
 * main - reads user input and executes user commands using execve
 * Return: nothing
 */

int main(void)
{
        char *temp = "";
        size_t len = 0;
        pid_t pid;
        ssize_t read;
        char *tok = NULL;
        char *args[1024];
        int i = 0;
        char *cpath = NULL;

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
                tok = strtok(temp, " ");
                while (tok != NULL)
                {
                        args[i++] = tok;
                        tok = strtok(NULL, " ");
                }
                args[i] = NULL;

                cpath = find_path(args[0], cpath);
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
                                perror("fork process failed");
                        else
                                waitpid(pid, NULL, 0);
                        free(cpath);
                }
                else
                        printf("%s: no such command or directory found\n", args[0]);
        }
        free(temp);
        return (0);
}
