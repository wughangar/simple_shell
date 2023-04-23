#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "main.h"

/**
 * _getline - Accepts a string from input steam as an input
 * @lineptr: a double pointer specifiying the place of the character array's initial character
 * @n: a pointer string to the array's size
 * @fd: stdin
 * Return: number of characters read
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
        ssize_t buffer_size = 128;
        ssize_t curr_pos = 0;
        int c;

        if (lineptr == NULL || n == NULL || stream == NULL)
                return (-1);
        *lineptr = malloc(buffer_size);
        if (*lineptr == NULL)
                return (-1);
	c = fgetc(stream);
	/*if (read_result < 0)
		return (-1); */

        while (c != EOF)
        {
                if (curr_pos >= buffer_size)
                {
                        buffer_size += 128;
                        *lineptr = realloc(*lineptr, buffer_size);
                        if (*lineptr == NULL)
                                return (-1);
                        *n = buffer_size;
                }
                (*lineptr)[curr_pos++] = c;
                if (c == '\n')
                        break;
        }
        if (curr_pos > 0 && (*lineptr)[curr_pos - 1] == '\n')
                (*lineptr)[curr_pos -1] = '\0';
        else
                (*lineptr)[curr_pos] = '\0';
        return (curr_pos);
}
