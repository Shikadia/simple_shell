#include "shell.h"

int (*checkbuiltin(char *cmd))(char **, char **arg0);
int exit_shell(char **args, char **arg0);
int _cd(char **args, char __attribute__((__unused__)) **arg0);

/**
 * checkbuiltin - Matches a command with the associated builtin function
 * @cmd: The command to match
 *
 * Return: Returns a function pointer to the associated builtin
 */
int (*checkbuiltin(char *cmd))(char **args, char **arg0)
{
	int i;

	bultns funclist[] = {
		{"exit", exit_shell},
		{"env", print_env},
		{"setenv", set_env},
		{"unsetenv", unset_env},
		{"cd", _cd },
		{NULL, NULL}
	};
	i = 0;
	while (funclist[i].name)
	{
		if (_strcmp(funclist[i].name, cmd) == 0)
			break;
		i++;
	}
	return (funclist[i].fpt);
}

/**
 * shellexit - Terminates program execution of the shell
 * @args: Array of arguments containing the exit value
 * @arg0: A double pointer to the start of the arguments
 *
 * Return: exits with the given status value
 *  if there is no argument, returns (-3)
 *  and -2 if the exit value is invalid
 */
int exit_shell(char **args, char **first)
{
	int i, maxLen = 10;
	unsigned int n = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			i = 1;
			maxLen++;
		}
		i = 0;
		while (args[0][i])
		{
			if (i <= maxLen && args[0][i] >= '0' && args[0][i] <= '9')
				n = (n * 10) + (args[0][i] - '0');
			else
				return (_error(--args, 2));
			i++;
		}
	}
	else
	{
		return (-3);
	}
	if (n > max - 1)
		return (_error(--args, 2));
	args -= 1;
	free_args(args, first);
	free_env();
	exit(n);
}

/**
 * _cd - Changes the current directory of the shell
 * @args: An array of arguments
 * @arg0: A double pointer to the beginning of args
 *
 * Return: returns when successful, -2
 * if not a directory nd -1 if error
 */
int _cd(char **args, char __attribute__((__unused__)) **first)
{
	struct stat dir;
	char **pathInfo, *newline = "\n", *prevdir = NULL, *pwd = NULL;

	prevdir = getcwd(prevdir, 0);
	if (!prevdir)
		return (-1);

	if (args[0])
	{
		if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') ||
					args[0][1] == '\0')
			{
				if (_getenv("OLDPWD") != NULL)
					(chdir(*_getenv("OLDPWD") + 7));
			}
			else
			{
				free(prevdir);
				return (_error(args, 2));
			}
		}
		else
		{
			if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(args[0]);
			else
			{
				free(prevdir);
				return (_error(args, 2));
			}
		}
	}
	else
	{
		if (_getenv("HOME") != NULL)
			chdir(*(_getenv("HOME")) + 5);
	}
	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	pathInfo = malloc(sizeof(char *) * 2);
	if (!pathInfo)
		return (-1);

	pathInfo[0] = "OLDPWD";
	pathInfo[1] = prevdir;
	if (set_env(pathInfo, pathInfo) == -1)
		return (-1);

	pathInfo[0] = "PWD";
	pathInfo[1] = pwd;
	if (set_env(pathInfo, pathInfo) == -1)
		return (-1);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, _strlen(pwd));
		write(STDOUT_FILENO, newline, 1);
	}
	free(prevdir);
	free(pwd);
	free(pathInfo);
	return (0);
}
