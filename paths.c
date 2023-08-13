#include "shell.h"

/**
 * path_loctor - Locates a command in the PATH
 * @cmd: The command to locate
 *
 * Return: On SUCCESS, returns the full path of the command and NULL on FAILURE
 */
char *path_locator(char *cmd)
{
	struct stat st;
	char **path, *tmp;
	lnkd_lst *dirs, *head;

	path = _getenv("PATH");
	if (!path || !(*path))
		return (NULL);
	dirs = retrive_path(*path + 5);
	head = dirs;
	while (dirs)
	{
		tmp = malloc(_strlen(dirs->dir) + _strlen(cmd) + 2);
		if (!tmp)
			return (NULL);
		_strcpy(tmp, dirs->dir);
		_strcat(tmp, "/");
		_strcat(tmp, cmd);
		if (stat(tmp, &st) == 0)
		{
			free_list(head);
			return (tmp);
		}
		dirs = dirs->next;
		free(tmp);
	}
	free_list(head);

	return (NULL);
}
