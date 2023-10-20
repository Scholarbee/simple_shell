#include "sshell.h"


void cInfo(my_arg_info *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}


void sInfo(my_arg_info *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = par_strtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = ut_strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		var_replace_alias(info);
		var_replace_vars(info);
	}
}


void fInfo(my_arg_info *info, int all)
{
	aa_ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->commandBuffer)
			free(info->arg);
		if (info->env)
			arr_free_list(&(info->env));
		if (info->history)
			arr_free_list(&(info->history));
		if (info->alias)
			arr_free_list(&(info->alias));
		aa_ffree(info->environ);
			info->environ = NULL;
		mem_bfree((void **)info->commandBuffer);
		if (info->readfd > 2)
			close(info->readfd);
		ut_putchar(BUF_FLUSH);
	}
}
