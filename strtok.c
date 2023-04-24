#include <stdio.h>
#include <string.h>
/**
 * _strtok - extracts tokens from strings
 * @str: pointer to the string being tokenized
 * @delim: delimiter
 * Return: pointer to the next token
 */

char *_strtok(char *str, const char *delim)
{
	static char *ltoken = NULL;
	char *tstart, *tend;

	if (str == NULL)
		str = ltoken;

	str += strspn(str, delim);
	if (*str == '\0')
		return (NULL);

	tstart = str;
	tend = strpbrk(tstart, delim);
	if (tend == NULL)
	{
		ltoken = strchr(tstart, '\0');
	}
	else
	{
		*tend = '\0';
		ltoken = tend + 1;
	}

	return (tstart);
}
