#include "shell.h"

char *get_args(char *line, int *ret);
int call_args(char **args, char **arg0, int *ret);
int run_args(char **args, char **arg0, int *ret);
int handle_args(int *ret);
int check_args(char **args);
void free_args(char **args, char **arg0);

/**
 * get_args - Gets a command from standard input
 * @line: A buffer to store the command
 * @ret: The return value of the last executed command
 *
 * Return: On SUCCESS, returns (line) ie a pointer to the stored command
 *	   On FAILURE, returns (NULL) to indicate an error occurred
 */
char *get_args(char *line, int *ret)
{
	char *prompt = "CIO:) ";
	size_t input = 0;
	ssize_t r;

	if (line)
		free(line);

	r = _getline(&line, &input, STDIN_FILENO);
	if (r == -1)
		return (NULL);
	if (r == 1)
	{
		cmdhistory++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 6);
		return (get_args(line, ret));
	}

	line[r - 1] = '\0';
	replace_var(&line, ret);
	split_line(&line, r);

	return (line);
}

/**
 * call_args - Separates operators from commands and calls the commands
 * @args: An array of arguments
 * @arg0: A 2D pointer to the start of args
 * @ret: The return value of the last executed command of the parent process
 *
 * Return: Returns the return value of the last executed command
 */
int call_args(char **args, char **arg0, int *ret)
{
	int ret_val, i;

	if (!args[0])
		return (*ret);
	i = 0;
	while (args[i])
	{
		if (_strncmp(args[i], "||", 2) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			ret_val = run_args(args, arg0, ret);
			if (*ret != 0)
			{
				args = &args[++i];
				i = 0;
			}
			else
			{
				for (i++; args[i]; i++)
					free(args[i]);
				return (ret_val);
			}
		}
		else if (_strncmp(args[i], "&&", 2) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			ret_val = run_args(args, arg0, ret);
			if (*ret == 0)
			{
				args = &args[++i];
				i = 0;
			}
			else
			{
				for (i++; args[i]; i++)
					free(args[i]);
				return (ret_val);
			}
		}
		i++;
	}
	ret_val = run_args(args, arg0, ret);
	return (ret_val);
}

/**
 * run_args - Calls the execution of a command
 * @args: An array of arguments
 * @arg0: A 2D pointer to the start of args
 * @ret: The return value of the last executed command of the parent process
 *
 * Return: Returns the return value of the last executed command
 */
int run_args(char **args, char **arg0, int *ret)
{
	int ret_val, i;
	int (*builtin)(char **args, char **arg0);

	builtin = checkbuiltin(args[0]);

	if (builtin)
	{
		ret_val = builtin(args + 1, arg0);
		if (ret_val != EXIT)
			*ret = ret_val;
	}
	else
	{
		*ret = execute(args, arg0);
		ret_val = *ret;
	}
	cmdhistory++;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}

	return (ret_val);
}

/**
 * handle_args - Gets, calls, and runs the execution of a command
 * @ret: The return value of the last executed command of the parent process
 *
 * Return: If end-of-file is read, returns _EOF
 *         If the input cannot be tokenized, returns -1
 *         Otherwise returns the exit value of the last executed command
 */
int handle_args(int *ret)
{
	char **args, **arg0, *line;
	int i, ret_val;

	ret_val = 0;
	line = NULL;
	line = get_args(line, ret);
	if (!line)
		return (_EOF);

	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (ret_val);
	if (check_args(args) != 0)
	{
		*ret = 2;
		free_args(args, args);
		return (*ret);
	}
	arg0 = args;
	i = 0;
	while (args[i])
	{
		if (_strncmp(args[i], ";", 1) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			ret_val = call_args(args, arg0, ret);
			args = &args[++i];
			i = 0;
		}
		i++;
	}
	if (args)
		ret_val = call_args(args, arg0, ret);
	free(arg0);

	return (ret_val);
}

/**
 * check_args - Checks if there are any leading ';', ';;', '&&', or '||'
 * @args: 2D pointer to tokenized commands and arguments
 *
 * Return: Returns (0) on SUCCESS
 *	   Returns (-2) if ';', '&&', or '||' is placed at an invalid position
 */
int check_args(char **args)
{
	char *currentchar, *nxt;
	size_t i;

	i = 0;
	while (args[i])
	{
		currentchar = args[i];
		if (currentchar[0] == ';' || currentchar[0] == '&'
			|| currentchar[0] == '|')
		{
			if (i == 0 || currentchar[1] == ';')
				return (_error(&args[i], 2));
			nxt = args[i + 1];
			if (nxt && (nxt[0] == ';' || nxt[0] == '&' || nxt[0] == '|'))
				return (_error(&args[i + 1], 2));
		}
		i++;
	}
	return (0);
}

/**
 * free_args - Frees up memory taken by args
 * @args: A 2D pointer to the commands entered
 * @arg0: A 2D pointer to the start of the arguments
 */
void free_args(char **args, char **arg0)
{
	size_t i;

	i = 0;
	while (args[i] || args[i + 1])
	{
		free(args[i]);
		i++;
	}
	free(arg0);
}
