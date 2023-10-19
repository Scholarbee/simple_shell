#include "sshell.h"

/**
 * var_is_chain - a function that test if current char in buffer is a chain delimeter
 * @ptr_info: the parameter struct
 * @bfer: the char buffer
 * @ptr_p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int var_is_chain(arg_info *ptr_info, char *bfer, size_t *ptr_p)
{
	size_t e = *ptr_p;

	if (bfer[e] == '|' && bfer[e + 1] == '|')
	{
		bfer[e] = 0;
		e++;
		ptr_info->commandBufferType = CMD_OR;
	}
	else if (bfer[e] == '&' && bfer[e + 1] == '&')
	{
		bfer[e] = 0;
		e++;
		ptr_info->commandBufferType = CMD_AND;
	}
	else if (bfer[e] == ';') /* found end of this command */
	{
		bfer[e] = 0; /* replace semicolon with null */
		ptr_info->commandBufferType = CMD_CHAIN;
	}
	else
		return (0);
	*ptr_p = e;
	return (1);
}

/**
 * var_check_chain - a function that checks if we should continue chaining based on last status
 * @ptr_info: the parameter struct
 * @bfer: the char buffer
 * @ptr_p: address of current position in buf
 * @j: starting position in buf
 * @l: length of buf
 *
 * Return: Void
 */
void var_check_chain(arg_info *ptr_info, char *bfer, size_t *ptr_p, size_t j, size_t l)
{
	size_t i = *ptr_p;

	if (ptr_info->commandBufferType == CMD_AND)
	{
		if (ptr_info->status)
		{
			bfer[j] = 0;
			i = l;
		}
	}
	if (ptr_info->commandBufferType == CMD_OR)
	{
		if (!ptr_info->status)
		{
			bfer[j] = 0;
			i = l;
		}
	}

	*ptr_p = i;
}

/**
 * var_replace_alias - a function that replaces an aliases in the tokenized string
 * @ptr_info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int var_replace_alias(arg_info *ptr_info)
{
	int i;
	list_t *node;
	char *ptr_p;

	for (i = 0; i < 10; i++)
	{
		node = arr_node_starts_with(ptr_info->alias, ptr_info->argv[0], '=');
		if (!node)
			return (0);
		free(ptr_info->argv[0]);
		ptr_p = qt_strchr(node->str, '=');
		if (!ptr_p)
			return (0);
		ptr_p = ut_strdup(ptr_p + 1);
		if (!ptr_p)
			return (0);
		ptr_info->argv[0] = ptr_p;
	}
	return (1);
}

/**
 * var_replace_vars - a function that replaces vars in the tokenized string
 * @ptr_info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int var_replace_vars(arg_info *ptr_info)
{
	int i = 0;
	list_t *node;

	for (i = 0; ptr_info->argv[i]; i++)
	{
		if (ptr_info->argv[i][0] != '$' || !ptr_info->argv[i][1])
			continue;

		if (!ut_strcmp(ptr_info->argv[i], "$?"))
		{
			var_replace_string(&(ptr_info->argv[i]),
				ut_strdup(eh_convert_number(ptr_info->status, 10, 0)));
			continue;
		}
		if (!ut_strcmp(ptr_info->argv[i], "$$"))
		{
			var_replace_string(&(ptr_info->argv[i]),
				ut_strdup(eh_convert_number(getpid(), 10, 0)));
			continue;
		}
		node = arr_node_starts_with(ptr_info->env, &ptr_info->argv[i][1], '=');
		if (node)
		{
			var_replace_string(&(ptr_info->argv[i]),
				ut_strdup(qt_strchr(node->str, '=') + 1));
			continue;
		}
		var_replace_string(&ptr_info->argv[i], ut_strdup(""));

	}
	return (0);
}

/**
 * var_replace_string - a function that replaces string
 * @ptr_old: address of old string
 * @ptr_new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int var_replace_string(char **ptr_old, char *ptr_new)
{
	free(*ptr_old);
	*ptr_old = ptr_new;
	return (1);
}
