#include "shell.h"

char **_envcopy(void);
void free_env(void);
char **_getenv(const char *var);
char *env_value(char *var, int len);
/**
 * _envcopy - Creates a copy of the environment
 *
 * Return: returns double pointer to the new copy
 */
char **_envcopy(void)
{
	int i;
	size_t size;
	char **new_env;

	size = 0;
	while (environ[size])
		size++;

	new_env = malloc(sizeof(char *) * (size + 1));
	if (!new_env)
		return (NULL);

	i = 0;
	while (environ[i])
	{
		new_env[i] = malloc(_strlen(environ[i]) + 1);

		if (!new_env[i])
		{
			i--;
			while (i >= 0)
			{
				free(new_env[i]);
				i--;
			}
			free(new_env);
			return (NULL);
		}
		_strcpy(new_env[i], environ[i]);
		i++;
	}
	new_env[i] = NULL;

	return (new_env);
}

/**
 * free_env - Frees the environment copy
 *
 * Return: Returns nothing (void)
 */
void free_env(void)
{
	int i;

	i = 0;
	while (environ[i])
	{
		free(environ[i]);
		i++;
	}
	free(environ);
}

/**
 * _getenv - Gets an environment variable from the PATH
 * @var: The name of the environment variable to get
 *
 * Return: On SUCCESS, returns (value) ie a pointer to the environ variable
 *         On FAILURE, returns (NULL) to indicate the variable does not exist
 */
char **_getenv(const char *var)
{
	int i, len;

	len = _strlen(var);
	i = 0;
	while (environ[i])
	{
		if (_strncmp(var, environ[i], len) == 0)
			return (&environ[i]);
		i++;
	}
	return (NULL);
}

/**
 * env_value - Gets the value associated with an environment variable
 * @var: The environment variable to search for
 * @len: The length of the environment variable to search for
 *
 * Return: On SUCCESS, returns (env_fetched) ie the value of the env variable
 *	   On FAILURE, returns (NULL) to indicate env variable is not found
 *
 */
char *env_value(char *var, int len)
{
	char *i, *env_name, **env_addr, *env_fetched = NULL;

	env_name = malloc(len + 1);
	if (!env_name)
		return (NULL);
	env_name[0] = '\0';
	_strncat(env_name, var, len);

	env_addr = _getenv(env_name);
	free(env_name);
	if (env_addr)
	{
		i = *env_addr;
		while (*i != '=')
			i++;
		i++;
		env_fetched = malloc(_strlen(i) + 1);
		if (env_fetched)
			_strcpy(env_fetched, i);
	}
	return (env_fetched);
}
