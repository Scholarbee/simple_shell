#include "sshell.h"

/**
 * env_my_env - a function that prints the current environment
 * @info: Structure containing potential arguments
 * Return: Always 0
 */
int env_my_env(arg_info *ptr_info)
{
	arr_print_list_str(ptr_info->env);
	return (0);
}

/**
 * env_my_get_env - a function that gets the value of an environment variable
 * @ptr_info: Structure containing potential arguments.
 * @name: env var name
 *
 * Return: the value
 */
char *env_my_get_env(arg_info *ptr_info, const char *n)
{
	list_t *ptr_node = ptr_info->env;
	char *mem;

	while (ptr_node)
	{
		mem = ut_starts_with(ptr_node->str, n);
		if (mem && *mem)
			return (mem);
		ptr_node = ptr_node->next;
	}
	return (NULL);
}

/**
 * env_my_set_env - a function that set a new environment variable,
 *             or change an existing one
 * @ptr_info: Structure containing possible arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int env_my_set_env(arg_info *ptr_info)
{
	if (ptr_info->argc != 3)
	{
		eh_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_set_env(ptr_info, ptr_info->argv[1], ptr_info->argv[2]))
		return (0);
	return (1);
}

/**
 * env_my_unset_env - Remove an environment variable
 * @info: Structure containing possible arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int env_my_unset_env(arg_info *ptr_info)
{
	int index;

	if (ptr_info->argc == 1)
	{
		eh_eputs("Arguments to few.\n");
		return (1);
	}
	for (index = 1; index <= ptr_info->argc; index++)
		_unset_env(ptr_info, ptr_info->argv[index]);

	return (0);
}

/**
 * env_populate_env_list - a function that populates env linked list
 * @ptr_info: Structure containing possible arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int env_populate_env_list(arg_info *ptr_info)
{
	list_t *ptr_node = NULL;
	size_t index;

	for (index = 0; environ[index]; index++)
		arr_add_node_end(&ptr_node, environ[index], 0);
	ptr_info->env = ptr_node;
	return (0);
}
