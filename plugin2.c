#include "sshell.h"


int pi_myhistory(my_arg_info *info)
{
	print_arr(info->history);
	return (0);
}


int pi_unset_alias(my_arg_info *info, char *str)
{
	char *p, c;
	int ret;

	p = qt_strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = arr_delete_node_at_index(&(info->alias),
		arr_get_node_index(info->alias, arr_node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}


int pi_set_alias(my_arg_info *info, char *str)
{
	char *ptr;

	ptr = qt_strchr(str, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (pi_unset_alias(info, str));

	pi_unset_alias(info, str);
	return (arr_add_node_end(&(info->alias), str, 0) == NULL);
}


int pi_print_alias(list_tbl *node)
{
	char *ptr = NULL, *a = NULL;

	if (node)
	{
		ptr = qt_strchr(node->p_str, '=');
		for (a = node->p_str; a <= ptr; a++)
			ut_putchar(*a);
		ut_putchar('\'');
		ut_puts(ptr + 1);
		ut_puts("'\n");
		return (0);
	}
	return (1);
}


int pi_myalias(my_arg_info *info)
{
	int i = 0;
	char *ptr = NULL;
	list_tbl *node = NULL;

	if (info->my_argc == 1)
	{
		node = info->alias;
		while (node)
		{
			pi_print_alias(node);
			node = node->nxt;
		}
		return (0);
	}
	for (i = 1; info->my_argv[i]; i++)
	{
		ptr = qt_strchr(info->my_argv[i], '=');
		if (ptr)
			pi_set_alias(info, info->my_argv[i]);
		else
			pi_print_alias(arr_node_starts_with(info->alias, info->my_argv[i], '='));
	}

	return (0);
}
