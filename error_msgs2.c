#include "shell.h"

char *error126(char **args);
char *error127(char **args);

/**
 * error126 - Creates an error message for permission denied failures
 * @args: An array of arguments passed to the command line
 *
 * Return: The error string
 *
 */
char *error126(char **args)
{
	int len;
	char *error, *hist;

	hist = _itoa(cmdhistory);
	if (!hist)
		return (NULL);

	len = _strlen(name) + _strlen(hist) + _strlen(args[0]) + 24;
	error = malloc(sizeof(*error) * (len + 1));
	if (!error)
	{
		free(hist);
		return (NULL);
	}
	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": Permission denied\n");

	free(hist);
	return (error);
}

/**
 * error127 - Creates an error message for command not found failures
 * @args: An array of arguments passed to the command line
 *
 * Return: The error string.
 */
char *error127(char **args)
{
	int len;
	char *error, *hist;

	hist = _itoa(cmdhistory);
	if (!hist)
		return (NULL);

	len = _strlen(name) + _strlen(hist) + _strlen(args[0]) + 16;
	error = malloc(sizeof(*error) * (len + 1));
	if (!error)
	{
		free(hist);
		return (NULL);
	}
	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": not found\n");

	free(hist);
	return (error);
}
