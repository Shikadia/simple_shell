#include "shell.h"

char *get_pid(void);
void replace_var(char **args, int *ret);
/**
 * replace_var - Handles variable replacement
 * @args: A 2D pointer containing the command line arguments
 * @ret: A pointer to the return value of the last command
 *
 * Return: returns void.
 */
void replace_var(char **args, int *ret)
{
	int len, i, j;
	char *new_line, *old_line, *value;

	old_line = *args;
	i = 0;
	value = NULL;
	j = 0;
	while (old_line[i])
	{
		if (old_line[i] == '$' && old_line[i + 1] && old_line[i + 1] != ' ')
		{
			if (old_line[i + 1] == '$')
			{
				value = get_pid();
				j = i + 2;
			}
			else if (old_line[i + 1] == '?')
			{
				value = _itoa(*ret);
				j = i + 2;
			}
			else if (old_line[i + 1])
			{
				j = i + 1;
				while (old_line[j] && old_line[j] != '$' && old_line[j] != ' ')
					j++;
				len = j - (i + 1);
				value = env_value(&old_line[i + 1], len);
			}
			new_line = malloc(i + _strlen(value) + _strlen(&old_line[j]) + 1);
			if (!args)
				return;
			new_line[0] = '\0';
			_strncat(new_line, old_line, i);
			if (value)
			{
				_strcat(new_line, value);
				free(value);
				value = NULL;
			}
			_strcat(new_line, &old_line[j]);
			free(old_line);
			*args = new_line;
			old_line = new_line;
			i = -1;
		}
		i++;
	}
}

/**
 * get_pid - Gets the current process ID of the shell
 *
 * Return: returns the current process ID
 */
char *get_pid(void)
{
	char *pid;
	size_t i;
	ssize_t file;

	i = 0;
	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	pid = malloc(128);
	if (!pid)
	{
		close(file);
		return (NULL);
	}
	read(file, pid, 128);
	while (pid[i] != ' ')
		i++;
	pid[i] = '\0';
	close(file);

	return (pid);
}
