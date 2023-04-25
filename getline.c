#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

/**
 * _getline - Accepts a string from input steam as an input
 * @lineptr: double pointer specifiying the place of the initial character
 * @n: a pointer string to the array's size
 * @fd: stdin
 * Return: number of characters read
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	const size_t init_alloc = 16;
	const size_t alloc_step = 16;
	size_t curr_pos = 0;
	size_t size_max = 1;
	int c;
	char *tmp;


	if (lineptr == NULL || n == NULL || stream == NULL)
		return (-1);
	if (*lineptr == NULL)
	{
		*lineptr = malloc(init_alloc);
		if (*lineptr == NULL)
			return (-1);
		else
			*n = init_alloc;
	}
	{
		while ((c = getc(stream)) != EOF)
		{
			curr_pos++;
			if (curr_pos >= *n)
			{
				size_t n_realloc = *n + alloc_step;
				tmp = realloc(*lineptr, n_realloc + 1);
				if (tmp != NULL)
				{
					*lineptr = tmp;
					*n = n_realloc;
				}
				else
					return (-1);
				if (size_max < *n)
				{
					perror("Error\n");
					return (-1);
				}
			}
			(*lineptr)[curr_pos - 1] = (char) c;
			if (c == '\n')
				break;
		}
		if (c == EOF)
		{
			perror("Error");
			return (-1);
		}
	}
	(*lineptr)[curr_pos] = '\0';
	return ((ssize_t) curr_pos);
}
