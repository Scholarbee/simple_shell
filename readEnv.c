#include "sshell.h"


char **_get_env(arg_info *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = arr_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}


int _unset_env(arg_info *info, char *var)
{
	list_tbl *node = info->env;
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


int _set_env(arg_info *info, char *var, char *val)
{
	char *buffer = NULL;
	list_tbl *node;
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
