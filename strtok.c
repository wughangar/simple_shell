#include <stdio.h>
/**
 * _strtok - extracts tokens from strings
 * @str: pointer to the string being tokenized
 * @delim: delimiter
 * Return: pointer to the next token
 */

char *_strtok(char *str, const char *delim)
{
	int i = 0, j, k;
	
	while (str[i] != '\0')
	{
		while (str[i] == ' ')
			i++;
		j = i;
		while (str[j] != ' ' && str[j] != '\0')
			j++;
		if (i != j)
		{
			for (k = i; k < j; k++)
				return(*str[k]);
		}
	}
}
