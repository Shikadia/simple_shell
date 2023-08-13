#include "shell.h"

int _toklen(char *str, char *delim);
int _tokcount(char *str, char *delim);
char **_strtok(char *line, char *delim);

/**
 * _toklen - Finds the delimiter marking the end of a string
 * @str: The string to obtain the len
 * @delim: The delimiter
 *
 * Return: Returns (len) ie the delimiter len
 */
int _toklen(char *str, char *delim)
{
	int i, len;

	i = 0;
	len = 0;
	while (*(str + i) && *(str + i) != *delim)
	{
		len++;
		i++;
	}
	return (len);
}

/**
 * _tokcount - Counts the number of delimited words in a string
 * @str: The string to count
 * @delim: The delimiter
 *
 * Return: returns the number of words contained within.
 */
int _tokcount(char *str, char *delim)
{
	int i, tokens, len;

	i = 0;
	len = 0;
	tokens = 0;
	while (*(str + i))
	{
		len++;
		i++;
	}

	i = 0;
	while (i < len)
	{
		if (*(str + i) != *delim)
		{
			tokens++;
			i += _toklen(str + i, delim);
		}
		i++;
	}
	return (tokens);
}

/**
 * _strtok - Tokenizes a string.
 * @line: The string.
 * @delim: The delimiter character to tokenize the string by.
 *
 * Return: Returns a pointer to an array of the tokenized words
 */
char **_strtok(char *line, char *delim)
{
	int i, tokens, t, letters, l;
	char **ptr;

	i = 0;
	tokens = _tokcount(line, delim);
	if (tokens == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (tokens + 2));
	if (!ptr)
		return (NULL);

	t = 0;
	while (t < tokens)
	{
		while (line[i] == *delim)
			i++;

		letters = _toklen(line + i, delim);

		ptr[t] = malloc(sizeof(char) * (letters + 1));
		if (!ptr[t])
		{
			for (i -= 1; i >= 0; i--)
				free(ptr[i]);
			free(ptr);
			return (NULL);
		}
		l = 0;
		while (l < letters)
		{
			ptr[t][l] = line[i];
			i++;
			l++;
		}
		ptr[t][l] = '\0';
		t++;
	}
	ptr[t] = NULL;
	ptr[t + 1] = NULL;

	return (ptr);
}
