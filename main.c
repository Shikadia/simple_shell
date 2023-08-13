#include "shell.h"

int main(int ac, char **av);
/**
 * main - Runs a simple UNIX command interpreter
 * @ac: The number of arguments from the command line
 * @av: An array of argument strings from the command line
 *
 * Return: returns the value of the last executed command
 */
int main(int ac, char **av)
{
	char *prompt = "CIO:) ", *newline = "\n";
	int ret_val, exec_retn;
	int *ret = &exec_retn;

	ret_val = 0;
	name = av[0];
	cmdhistory = 1;
	signal(SIGINT, handle_sig);

	*ret = 0;
	environ = _envcopy();
	if (!environ)
		exit(-100);

	if (ac != 1)
	{
		ret_val = run_commands(av[1], ret);
		free_env();
		return (*ret);
	}
	if (!isatty(STDIN_FILENO))
	{
		while (ret_val != _EOF && ret_val != EXIT)
			ret_val = handle_args(ret);
		free_env();
		return (*ret);
	}
	while (1)
	{
		write(STDOUT_FILENO, prompt, 6);
		ret_val = handle_args(ret);
		if (ret_val == _EOF || ret_val == EXIT)
		{
			if (ret_val == _EOF)
				write(STDOUT_FILENO, newline, 1);
			free_env();
			exit(*ret);
		}
	}
	free_env();
	return (*ret);
}
