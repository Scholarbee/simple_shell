#include "sshell.h"


int ss_hsh(my_arg_info *info, char **av)
{
	ssize_t r = 0;
	int bltin_ret = 0;

	while (r != -1 && bltin_ret != -2)
	{
		cInfo(info);
		if (conv_interactive(info))
			ut_puts("$ ");
		eh_eputchar(BUF_FLUSH);
		r = gInput(info);
		if (r != -1)
		{
			sInfo(info, av);
			bltin_ret = ss_find_builtin(info);
			if (bltin_ret == -1)
				ss_find_cmd(info);
		}
		else if (conv_interactive(info))
			ut_putchar('\n');
		fInfo(info, 0);
	}
	write_past(info);
	fInfo(info, 1);
	if (!conv_interactive(info) && info->my_status)
		exit(info->my_status);
	if (bltin_ret == -2)
	{
		if (info->my_err_num == -1)
			exit(info->my_status);
		exit(info->my_err_num);
	}
	return (bltin_ret);
}


int ss_find_builtin(my_arg_info *info)
{
	int i, blt_in_ret = -1;
	blt_in_tbl bltintbl[] = {
		{"help", pi_myhelp},
		{"env", env_my_env},
		{"history", pi_myhistory},
		{"alias", pi_myalias},
		{"setenv", env_my_set_env},
		{"unsetenv", env_my_unset_env},
		{"cd", pi_mycd},
		{"exit", pi_myexit},
		{NULL, NULL}
	};

	for (i = 0; bltintbl[i].ptype; i++)
		if (ut_strcmp(info->my_argv[0], bltintbl[i].ptype) == 0)
		{
			info->my_count_line++;
			blt_in_ret = bltintbl[i].my_func(info);
			break;
		}
	return (blt_in_ret);
}


void ss_find_cmd(my_arg_info *info)
{
	char *path = NULL;
	int i, k;

	info->my_path = info->my_argv[0];
	if (info->my_lc_flag == 1)
	{
		info->my_count_line++;
		info->my_lc_flag = 0;
	}
	for (i = 0, k = 0; info->my_arg[i]; i++)
		if (!conv_is_delim(info->my_arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = parse_find_path(info, env_my_get_env(info, "PATH="), info->my_argv[0]);
	if (path)
	{
		info->my_path = path;
		ss_fork_cmd(info);
	}
	else
	{
		if ((conv_interactive(info) || env_my_get_env(info, "PATH=")
			|| info->my_argv[0][0] == '/') && parse_is_cmd(info, info->my_argv[0]))
			ss_fork_cmd(info);
		else if (*(info->my_arg) != '\n')
		{
			info->my_status = 127;
			eh_print_error(info, "not found\n");
		}
	}
}


void ss_fork_cmd(my_arg_info *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->my_path, info->my_argv, _get_env(info)) == -1)
		{
			fInfo(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		
	}
	else
	{
		wait(&(info->my_status));
		if (WIFEXITED(info->my_status))
		{
			info->my_status = WEXITSTATUS(info->my_status);
			if (info->my_status == 126)
				eh_print_error(info, "Permission denied\n");
		}
	}
}
