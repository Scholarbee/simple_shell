#include "sshell.h"

/**
 * pi_myhistory - a function that displays the history list
 *
 * @info: Structure containing possible arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int pi_myhistory(arg_info *info)
{
	print_arr(info->history);
	return (0);
}

/**
 * pi_unset_alias - a function that sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int pi_unset_alias(arg_info *info, char *str)
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

/**
 * pi_set_alias - a function that sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int pi_set_alias(arg_info *info, char *str)
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

/**
 * pi_print_alias - a function that prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int pi_print_alias(list_t *node)
{
	char *ptr = NULL, *a = NULL;

	if (node)
	{
		ptr = qt_strchr(node->str, '=');
		for (a = node->str; a <= ptr; a++)
			ut_putchar(*a);
		ut_putchar('\'');
		ut_puts(ptr + 1);
		ut_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * pi_myalias - a function that emitate the alias builtin (man alias)
 * @info: Structure containing possible arguments.
 *
 *  Return: Always 0
 */
int pi_myalias(arg_info *info)
{
	int i = 0;
	char *ptr = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			pi_print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		ptr = qt_strchr(info->argv[i], '=');
		if (ptr)
			pi_set_alias(info, info->argv[i]);
		else
			pi_print_alias(arr_node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
