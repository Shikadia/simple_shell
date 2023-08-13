#include "shell.h"

char *env_error(char **args);
char *exit_error(char **args);
char *cd_error(char **args);
char *syntax_error(char **args);

/**
 * env_error - Creates an error message for the function '_printenv' errors
 * @args: An array of arguments passed to the command line
 *
 * Return: On SUCCESS, returns (error) ie the error string
 *	   On FAILURE, returns (NULL)
 */
char *env_error(char **args)
{
	int len;
	char *error, *hist_str;

	hist_str = _itoa(cmdhistory);
	if (!hist_str)
		return (NULL);
	args--;
	len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 45;
	error = malloc(sizeof(*error) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}
	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": Unable to add/remove from environment\n");

	free(hist_str);
	return (error);
}

/**
 * exit_error - Creates an error message for shellexit errors
 * @args: An array of arguments passed to the command line
 *
 * Return: On SUCCESS, returns (error) ie the error string
 *	   On FAILURE, returns (NULL)
 */
char *exit_error(char **args)
{
	int len;
	char *error, *hist;

	hist = _itoa(cmdhistory);
	if (!hist)
		return (NULL);

	len = _strlen(name) + _strlen(hist) + _strlen(args[0]) + 27;
	error = malloc(sizeof(*error) * (len + 1));
	if (!error)
	{
		free(hist);
		return (NULL);
	}
	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist);
	_strcat(error, ": exit: Illegal number: ");
	_strcat(error, args[0]);
	_strcat(error, "\n");

	free(hist);
	return (error);
}

/**
 * cd_error - Creates an error message for 'cd' errors
 * @args: An array of arguments passed to the command line
 *
 * Return: On SUCCESS, returns (error) ie the error string
 *	   On FAILURE, returns (NULL)
 */
char *cd_error(char **args)
{
	int len;
	char *error, *hist;

	hist = _itoa(cmdhistory);
	if (!hist)
		return (NULL);

	if (args[0][0] == '-')
		args[0][2] = '\0';
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
	if (args[0][0] == '-')
		_strcat(error, ": cd: Illegal option ");
	else
		_strcat(error, ": cd: can't cd to ");
	_strcat(error, args[0]);
	_strcat(error, "\n");

	free(hist);
	return (error);
}

/**
 * syntax_error - Creates an error message for syntax errors
 * @args: An array of arguments passed to the command line
 *
 * Return: The error string
 */
char *syntax_error(char **args)
{
	int len;
	char *error, *hist;

	hist = _itoa(cmdhistory);
	if (!hist)
		return (NULL);

	len = _strlen(name) + _strlen(hist) + _strlen(args[0]) + 33;
	error = malloc(sizeof(*error) * (len + 1));
	if (!error)
	{
		free(hist);
		return (NULL);
	}
	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist);
	_strcat(error, ": Syntax error: \"");
	_strcat(error, args[0]);
	_strcat(error, "\" unexpected\n");

	free(hist);
	return (error);
}
