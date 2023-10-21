#include "sshell.h"


char **_get_env(my_arg_info *info)
{
	if (!info->my_environ || info->my_env_changed)
	{
		info->my_environ = arr_to_strings(info->my_env);
		info->my_env_changed = 0;
	}

	return (info->my_environ);
}


int _unset_env(my_arg_info *info, char *var)
{
	list_tbl *node = info->my_env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = ut_starts_with(node->p_str, var);
		if (p && *p == '=')
		{
			info->my_env_changed = arr_delete_node_at_index(&(info->my_env), i);
			i = 0;
			node = info->my_env;
			continue;
		}
		node = node->nxt;
		i++;
	}
	return (info->my_env_changed);
}


int _set_env(my_arg_info *info, char *var, char *val)
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
	node = info->my_env;
	while (node)
	{
		ptr = ut_starts_with(node->p_str, var);
		if (ptr && *ptr == '=')
		{
			free(node->p_str);
			node->p_str = buffer;
			info->my_env_changed = 1;
			return (0);
		}
		node = node->nxt;
	}
	arr_add_node_end(&(info->my_env), buffer, 0);
	free(buffer);
	info->my_env_changed = 1;
	return (0);
}
