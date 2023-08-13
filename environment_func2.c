#include "shell.h"

int print_env(char **args, char __attribute__((__unused__)) **arg0);
int set_env(char **args, char __attribute__((__unused__)) **arg0);
int unset_env(char **args, char __attribute__((__unused__)) **arg0);
/**
 * print_env - Prints the current environment
 * @args: An array of arguments passed to the shell
 * @arg0: A double pointer to the start of arguments
 *
 * Return: On SUCCESS,	returns (0)
 *	   On FAILURE,	returns (-1) to indicate an error occurred
 */
int print_env(char **args, char __attribute__((__unused__)) **arg0)
{
	int i;
	char newline = '\n';

	(void)args;
	if (!environ)
		return (-1);
	i = 0;
	while (environ[i])
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, &newline, 1);
		i++;
	}
	return (0);
}

/**
 * set_env - Adds or modifies an environmental variable
 * @args: An array of arguments
 * @arg0: A double pointer to the start of arguments
 *
 * Return: On SUCCESS, returns (0)
 *	   On FAILURE, returns (-1) to indicate an error occurred
 */
int set_env(char **args, char __attribute__((__unused__)) **arg0)
{
	int i;
	size_t size;
	char *new_env, **environ_array, **env = NULL;

	if (!args[0] || !args[1])
		return (_error(args, -1));

	new_env = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
	if (!new_env)
		return (_error(args, -1));
	_strcpy(new_env, args[0]);
	_strcat(new_env, "=");
	_strcat(new_env, args[1]);

	env = _getenv(args[0]);
	if (env)
	{
		free(*env);
		*env = new_env;
		return (0);
	}
	size = 0;
	while (environ[size])
		size++;
	environ_array = malloc(sizeof(char *) * (size + 2));
	if (!environ_array)
	{
		free(new_env);
		return (_error(args, -1));
	}

	i = 0;
	while (environ[i])
	{
		environ_array[i] = environ[i];
		i++;
	}

	free(environ);
	environ = environ_array;
	environ[i] = new_env;
	environ[i + 1] = NULL;

	return (0);
}

/**
 * unset_env - Deletes an environment variable from the PATH.
 * @args: An array of arguments passed to the shell.
 * @arg0: A double pointer to the beginning of args
 *
 * Return: On SUCCESS, returns (0)
 *	   On FAILURE, returns (-1) to indicate an error occurred
 */
int unset_env(char **args, char __attribute__((__unused__)) **arg0)
{
	int i, j;
	char **env, **new_env;
	size_t size;

	if (!args[0])
		return (_error(args, -1));
	env = _getenv(args[0]);
	if (!env)
		return (0);

	size = 0;
	while (environ[size])
		size++;
	new_env = malloc(sizeof(char *) * size);
	if (!new_env)
		return (_error(args, -1));
	i = 0;
	j = 0;
	while (environ[i])
	{
		if (*env == environ[i])
		{
			free(*env);
			continue;
		}
		new_env[j] = environ[i];
		j++;
		i++;
	}
	free(environ);
	environ = new_env;
	environ[size - 1] = NULL;

	return (0);
}
