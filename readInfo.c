#include "sshell.h"


void cInfo(my_arg_info *info)
{
	info->my_arg = NULL;
	info->my_argv = NULL;
	info->my_path = NULL;
	info->my_argc = 0;
}


void sInfo(my_arg_info *info, char **av)
{
	int i = 0;

	info->my_fname = av[0];
	if (info->my_arg)
	{
		info->my_argv = par_strtow(info->my_arg, " \t");
		if (!info->my_argv)
		{

			info->my_argv = malloc(sizeof(char *) * 2);
			if (info->my_argv)
			{
				info->my_argv[0] = ut_strdup(info->my_arg);
				info->my_argv[1] = NULL;
			}
		}
		for (i = 0; info->my_argv && info->my_argv[i]; i++)
			;
		info->my_argc = i;

		var_replace_alias(info);
		var_replace_vars(info);
	}
}


void fInfo(my_arg_info *info, int all)
{
	aa_ffree(info->my_argv);
	info->my_argv = NULL;
	info->my_path = NULL;
	if (all)
	{
		if (!info->my_commandBuffer)
			free(info->my_arg);
		if (info->my_env)
			arr_free_list(&(info->my_env));
		if (info->my_history)
			arr_free_list(&(info->my_history));
		if (info->my_alias)
			arr_free_list(&(info->my_alias));
		aa_ffree(info->my_environ);
			info->my_environ = NULL;
		mem_bfree((void **)info->my_commandBuffer);
		if (info->my_readfd > 2)
			close(info->my_readfd);
		ut_putchar(BUF_FLUSH);
	}
}
