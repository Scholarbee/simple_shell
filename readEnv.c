#include "sshell.h"

/**
 * _get_env - a funtion returns the string array copy of our environ
 * @info: Structure containing possible arguments.
 *
 * Return: Always 0
 */
char **_get_env(arg_info *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = arr_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unset_env - a function that deletes an environment variable
 * @info: Structure containing possible arguments.
*
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unset_env(arg_info *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = ut_starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = arr_delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _set_env - a function that set a new environment variable,
 *             or change an existing one
 * @info: Structure containing possible arguments.
 *
 * @var: the string env var property
 * @val: the string env var value
 *  Return: Always 0
 */
int _set_env(arg_info *info, char *var, char *val)
{
	char *buffer = NULL;
	list_t *node;
	char *ptr;

	if (!var || !val)
		return (0);

	buffer = malloc(ut_strlen(var) + ut_strlen(val) + 2);
	if (!buffer)
		return (1);
	ut_strcpy(buffer, var);
	ut_strcat(buffer, "=");
	ut_strcat(buffer, val);
	node = info->env;
	while (node)
	{
		ptr = ut_starts_with(node->str, var);
		if (ptr && *ptr == '=')
		{
			free(node->str);
			node->str = buffer;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	arr_add_node_end(&(info->env), buffer, 0);
	free(buffer);
	info->env_changed = 1;
	return (0);
}
