#include "shell.h"

void handle_sig(int sig __attribute__((unused)));
int execute(char **args, char **first);

/**
 * check_sig - Verifies if Ctrl+C key combination is pressed
 *	       and prints a new prompt upon a signal
 * @sig: The signal
 */
void handle_sig(int sig __attribute__((unused)))
{
	char *prompt = "\nCIO:) ";

	signal(SIGINT, handle_sig);
	write(STDIN_FILENO, prompt, 8);
}

/**
 * execute - Executes a command in a child process
 * @args: An array of arguments
 * @first: A double pointer to the start of args
 *
 * Return: On SUCCESS, returns the exit value of the last executed command
 *	   If an error occurs returns the associated error code
 */
int execute(char **args, char **first)
{
	pid_t pid;
	int status, flag, ret;
	char *cmd;

	flag = 0;
	ret = 0;
	cmd = args[0];
	if (cmd[0] != '/' && cmd[0] != '.')
	{
		flag = 1;
		cmd = path_locator(cmd);
	}
	if (!cmd || (access(cmd, F_OK) == -1))
	{
		if (errno == EACCES)
			ret = (_error(args, 126));
		else
			ret = (_error(args, 127));
	}
	else
	{
		pid = fork();
		if (pid == -1)
		{
			if (flag)
				free(cmd);
			perror("Error child:");
			return (1);
		}
		if (pid == 0)
		{
			execve(cmd, args, environ);
			if (errno == EACCES)
				ret = (_error(args, 126));
			free_env();
			free_args(args, first);
			_exit(ret);
		}
		else
		{
			wait(&status);
			ret = WEXITSTATUS(status);
		}
	}
	if (flag)
		free(cmd);
	return (ret);
}
