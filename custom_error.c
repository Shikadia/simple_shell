#include "shell.h"

/**
 * _error - Writes a custom error message to standard error (stderr)
 * @args: An array of arguments
 * @err: The error value
 *
 * Return: Returns (err) ie the error value
 */
int _error(char **args, int err)
{
	char *error;

	switch (err)
	{
	case -1:
		error = env_error(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			error = exit_error(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			error = syntax_error(args);
		else
			error = cd_error(args);
		break;
	case 126:
		error = error126(args);
		break;
	case 127:
		error = error127(args);
		break;
	}
	write(STDERR_FILENO, error, _strlen(error));

	if (error)
		free(error);

	return (err);
}
