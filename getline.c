#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
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
        char buffer[1024];
        size_t curr_pos = 0;
        ssize_t read_result = 0;
        char *new_ptr = NULL;
        char c;

        if (lineptr == NULL || n == NULL || stream == NULL)
                return (-1);
        while (1)
        {
                read_result = read(fileno(stream), &c, 1);
                if (read_result < 1)
                        break;
                if (curr_pos >= *n - 1){
                        *n *= 2;
                        new_ptr = realloc(*lineptr, *n);
                        if (!new_ptr)
                        {
                                free(*lineptr);
                                return (-1);
                        }
                        *lineptr = new_ptr;
                }
                buffer[curr_pos++] = c;
                if (c == '\n')
                {
                        buffer[curr_pos] = '\0';
                        *lineptr = realloc(*lineptr, curr_pos + 1);
                        if (*lineptr == NULL)
                        {
                                free(new_ptr);
                                return (-1);
                        }
                        memcpy(*lineptr, buffer, curr_pos + 1);
                        return (curr_pos);
                }
        }
        if (curr_pos == 0)
                return (-1);
        memcpy(*lineptr, buffer, curr_pos + 1);
        return (curr_pos);
}
