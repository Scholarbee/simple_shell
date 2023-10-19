#include "sshell.h"

/**
 * ss_hsh - main shell function
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int ss_hsh(arg_info *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		cInfo(info);
		if (conv_interactive(info))
			ut_puts("$ ");
		eh_eputchar(BUF_FLUSH);
		r = gInput(info);
		if (r != -1)
		{
			sInfo(info, av);
			builtin_ret = ss_find_builtin(info);
			if (builtin_ret == -1)
				ss_find_cmd(info);
		}
		else if (conv_interactive(info))
			ut_putchar('\n');
		fInfo(info, 0);
	}
	write_past(info);
	fInfo(info, 1);
	if (!conv_interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * ss_find_builtin - a function that finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int ss_find_builtin(arg_info *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", pi_myexit},
		{"env", env_my_env},
		{"help", pi_myhelp},
		{"history", pi_myhistory},
		{"setenv", env_my_set_env},
		{"unsetenv", env_my_unset_env},
		{"cd", pi_mycd},
		{"alias", pi_myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (ut_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->count_line++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * ss_find_cmd - a function that finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void ss_find_cmd(arg_info *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->lc_flag == 1)
	{
		info->count_line++;
		info->lc_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!conv_is_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = parse_find_path(info, env_my_get_env(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		ss_fork_cmd(info);
	}
	else
	{
		if ((conv_interactive(info) || env_my_get_env(info, "PATH=")
			|| info->argv[0][0] == '/') && parse_is_cmd(info, info->argv[0]))
			ss_fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			eh_print_error(info, "not found\n");
		}
	}
}

/**
 * ss_fork_cmd - a function that forks an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void ss_fork_cmd(arg_info *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, _get_env(info)) == -1)
		{
			fInfo(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				eh_print_error(info, "Permission denied\n");
		}
	}
}
