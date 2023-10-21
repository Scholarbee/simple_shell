#include "sshell.h"


int env_my_env(my_arg_info *ptr_info)
{
	arr_print_list_str(ptr_info->my_env);
	return (0);
}


char *env_my_get_env(my_arg_info *ptr_info, const char *n)
{
	list_tbl *ptr_node = ptr_info->my_env;
	char *mem;

	while (ptr_node)
	{
		mem = ut_starts_with(ptr_node->p_str, n);
		if (mem && *mem)
			return (mem);
		ptr_node = ptr_node->nxt;
	}
	return (NULL);
}


int env_my_set_env(my_arg_info *ptr_info)
{
	if (ptr_info->my_argc != 3)
	{
		eh_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_set_env(ptr_info, ptr_info->my_argv[1], ptr_info->my_argv[2]))
		return (0);
	return (1);
}


int env_my_unset_env(my_arg_info *ptr_info)
{
	int index;

	if (ptr_info->my_argc == 1)
	{
		eh_eputs("Arguments to few.\n");
		return (1);
	}
	for (index = 1; index <= ptr_info->my_argc; index++)
		_unset_env(ptr_info, ptr_info->my_argv[index]);

	return (0);
}


int env_populate_env_list(my_arg_info *ptr_info)
{
	list_tbl *ptr_node = NULL;
	size_t index;

	for (index = 0; environ[index]; index++)
		arr_add_node_end(&ptr_node, environ[index], 0);
	ptr_info->my_env = ptr_node;
	return (0);
}
