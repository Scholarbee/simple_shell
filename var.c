#include "sshell.h"


int var_is_chain(my_arg_info *ptr_info, char *bfer, size_t *ptr_p)
{
	size_t e = *ptr_p;

	if (bfer[e] == '|' && bfer[e + 1] == '|')
	{
		bfer[e] = 0;
		e++;
		ptr_info->my_commandBufferType = CMD_OR;
	}
	else if (bfer[e] == '&' && bfer[e + 1] == '&')
	{
		bfer[e] = 0;
		e++;
		ptr_info->my_commandBufferType = CMD_AND;
	}
	else if (bfer[e] == ';')
	{
		bfer[e] = 0;
		ptr_info->my_commandBufferType = CMD_CHAIN;
	}
	else
		return (0);
	*ptr_p = e;
	return (1);
}


void var_check_chain(my_arg_info *ptr_info, char *bfer, size_t *ptr_p, size_t j, size_t l)
{
	size_t i = *ptr_p;

	if (ptr_info->my_commandBufferType == CMD_AND)
	{
		if (ptr_info->my_status)
		{
			bfer[j] = 0;
			i = l;
		}
	}
	if (ptr_info->my_commandBufferType == CMD_OR)
	{
		if (!ptr_info->my_status)
		{
			bfer[j] = 0;
			i = l;
		}
	}

	*ptr_p = i;
}


int var_replace_alias(my_arg_info *ptr_info)
{
	int i;
	list_tbl *node;
	char *ptr_p;

	for (i = 0; i < 10; i++)
	{
		node = arr_node_starts_with(ptr_info->my_alias, ptr_info->my_argv[0], '=');
		if (!node)
			return (0);
		free(ptr_info->my_argv[0]);
		ptr_p = qt_strchr(node->p_str, '=');
		if (!ptr_p)
			return (0);
		ptr_p = ut_strdup(ptr_p + 1);
		if (!ptr_p)
			return (0);
		ptr_info->my_argv[0] = ptr_p;
	}
	return (1);
}


int var_replace_vars(my_arg_info *ptr_info)
{
	int i = 0;
	list_tbl *node;

	for (i = 0; ptr_info->my_argv[i]; i++)
	{
		if (ptr_info->my_argv[i][0] != '$' || !ptr_info->my_argv[i][1])
			continue;

		if (!ut_strcmp(ptr_info->my_argv[i], "$?"))
		{
			var_replace_string(&(ptr_info->my_argv[i]),
				ut_strdup(eh_convert_number(ptr_info->my_status, 10, 0)));
			continue;
		}
		if (!ut_strcmp(ptr_info->my_argv[i], "$$"))
		{
			var_replace_string(&(ptr_info->my_argv[i]),
				ut_strdup(eh_convert_number(getpid(), 10, 0)));
			continue;
		}
		node = arr_node_starts_with(ptr_info->my_env, &ptr_info->my_argv[i][1], '=');
		if (node)
		{
			var_replace_string(&(ptr_info->my_argv[i]),
				ut_strdup(qt_strchr(node->p_str, '=') + 1));
			continue;
		}
		var_replace_string(&ptr_info->my_argv[i], ut_strdup(""));

	}
	return (0);
}


int var_replace_string(char **ptr_old, char *ptr_new)
{
	free(*ptr_old);
	*ptr_old = ptr_new;
	return (1);
}
