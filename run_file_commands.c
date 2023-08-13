#include "shell.h"

int file_open_error(char *path);
int run_commands(char *path, int *ret);

/**
 * file_open_error - Prints assigned error if file can't be opened or accessed
 * @path: Path to the file
 *
 * Return: Returns (127)
 */
int file_open_error(char *path)
{
	int len;
	char *error, *histStr;

	histStr = _itoa(cmdhistory);
	if (!histStr)
		return (127);

	len = _strlen(name) + _strlen(histStr) + _strlen(path) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(histStr);
		return (127);
	}
	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, histStr);
	_strcat(error, ": Can't open ");
	_strcat(error, path);
	_strcat(error, "\n");
	free(histStr);
	write(STDERR_FILENO, error, len);
	free(error);
	return (127);
}

/**
 * run_commands - Runs a file command stored within
 * @path: Path to the file
 * @ret: Return value of the last executed command
 *
 * Return: returns value of last command
 *         or apropriate error.
 */
int run_commands(char *path, int *ret)
{
	int ret_val;
	char *line, **args, **arg0, buffer[128];
	ssize_t file, bytes, i;
	unsigned int line_size = 0, old_size = 128;

	cmdhistory = 0;
	file = open(path, O_RDONLY);
	if (file == -1)
	{
		*ret = file_open_error(path);
		return (*ret);
	}
	line = malloc(sizeof(char) * old_size);
	if (!line)
		return (-1);
	do {
		bytes = read(file, buffer, 127);
		if (bytes == 0 && line_size == 0)
			return (*ret);
		buffer[bytes] = '\0';
		line_size += bytes;
		line = _realloc(line, old_size, line_size);
		_strcat(line, buffer);
		old_size = line_size;
	} while (bytes);
	i = 0;
	while (line[i] == '\n')
	{
		line[i] = ' ';
		i++;
	}
	while (i < line_size)
	{
		if (line[i] == '\n')
		{
			line[i] = ';';
			for (i += 1; i < line_size && line[i] == '\n'; i++)
				line[i] = ' ';
		}
		i++;
	}
	replace_var(&line, ret);
	split_line(&line, line_size);
	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (0);
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
	ret_val = call_args(args, arg0, ret);

	free(arg0);
	return (ret_val);
}
