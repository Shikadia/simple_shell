#include "shell.h"

lnkd_lst *retrive_path(char *path);
char *path_populator(char *path);
/**
 * path_populator - Copies and replaces leading colons
*  (:) with current directory
 * @path: Colon-separated list of directories
 *
 * Return: returns a duplicate path
 */
char *path_populator(char *path)
{
	char *pathdup, *pwd;
	int i, len;

	pwd = *(_getenv("PWD")) + 4;
	len = 0;
	i = 0;
	while (path[i])
	{
		if (path[i] == ':')
		{
			if (path[i + 1] == ':' || i == 0 || path[i + 1] == '\0')
				len += _strlen(pwd) + 1;
			else
				len++;
		}
		else
			len++;
		i++;
	}
	pathdup = malloc(sizeof(*pathdup) * (len + 1));
	if (!pathdup)
		return (NULL);
	pathdup[0] = '\0';
	i = 0;
	while (path[i])
	{
		if (path[i] == ':')
		{
			if (i == 0)
			{
				_strcat(pathdup, pwd);
				_strcat(pathdup, ":");
			}
			else if (path[i + 1] == ':' || path[i + 1] == '\0')
			{
				_strcat(pathdup, ":");
				_strcat(pathdup, pwd);
			}
			else
				_strcat(pathdup, ":");
		}
		else
			_strncat(pathdup, &path[i], 1);
		i++;
	}
	return (pathdup);
}

/**
 * retrive_path - Splits a colon-separated list of directories
 * @path: The colon-separated list of directories
 *
 * Return: Returns a pointer to the linked list
 */
lnkd_lst *retrive_path(char *path)
{
	char **dirs, *pathdup;
	int i;

	lnkd_lst *head = NULL;

	pathdup = path_populator(path);
	if (!pathdup)
		return (NULL);
	dirs = _strtok(pathdup, ":");
	free(pathdup);
	if (!dirs)
		return (NULL);
	i = 0;
	while (dirs[i])
	{
		if (add_endnode(&head, dirs[i]) == NULL)
		{
			free_list(head);
			free(dirs);
			return (NULL);
		}
		i++;
	}
	free(dirs);

	return (head);
}
