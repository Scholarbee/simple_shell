#include "sshell.h"

/**
 * pi_myexit - a function that exits the shell
 * @info: Structure containing potential arguments.
 *
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int pi_myexit(arg_info *info)
{
	int exit_check;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		exit_check = eh_erratoi(info->argv[1]);
		if (exit_check == -1)
		{
			info->status = 2;
			eh_print_error(info, "Illegal number: ");
			eh_eputs(info->argv[1]);
			eh_eputchar('\n');
			return (1);
		}
		info->err_num = eh_erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * pi_mycd - a function that changes the current directory of the process
 * @info: Structure containing possible arguments.
 *
 *  Return: Always 0
 */
int pi_mycd(arg_info *info)
{
	char *s, *dir, buffer[1024];
	int chdir_return;

	s = getcwd(buffer, 1024);
	if (!s)
		ut_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = env_my_get_env(info, "HOME=");
		if (!dir)
			chdir_return = /* TODO: what should this be? */
				chdir((dir = env_my_get_env(info, "PWD=")) ? dir : "/");
		else
			chdir_return = chdir(dir);
	}
	else if (ut_strcmp(info->argv[1], "-") == 0)
	{
		if (!env_my_get_env(info, "OLDPWD="))
		{
			ut_puts(s);
			ut_putchar('\n');
			return (1);
		}
		ut_puts(env_my_get_env(info, "OLDPWD=")), ut_putchar('\n');
		chdir_return = /* TODO: what should this be? */
			chdir((dir = env_my_get_env(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_return = chdir(info->argv[1]);
	if (chdir_return == -1)
	{
		eh_print_error(info, "can't cd to ");
		eh_eputs(info->argv[1]), eh_eputchar('\n');
	}
	else
	{
		_set_env(info, "OLDPWD", env_my_get_env(info, "PWD="));
		_set_env(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * pi_myhelp - a function that changes the current directory of the process
 * @info: Structure containing possible arguments.
 *
 *  Return: Always 0
 */
int pi_myhelp(arg_info *info)
{
	char **arg_array;

	arg_array = info->argv;
	ut_puts("help call works. Function not yet implemented \n");
	if (0)
		ut_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
