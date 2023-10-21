#include "sshell.h"


int pi_myexit(my_arg_info *info)
{
	int exit_check;

	if (info->my_argv[1])  
	{
		exit_check = eh_erratoi(info->my_argv[1]);
		if (exit_check == -1)
		{
			info->my_status = 2;
			eh_print_error(info, "Illegal number: ");
			eh_eputs(info->my_argv[1]);
			eh_eputchar('\n');
			return (1);
		}
		info->my_err_num = eh_erratoi(info->my_argv[1]);
		return (-2);
	}
	info->my_err_num = -1;
	return (-2);
}


int pi_mycd(my_arg_info *info)
{
	char *s, *dir, buffer[1024];
	int chdir_return;

	s = getcwd(buffer, 1024);
	if (!s)
		ut_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->my_argv[1])
	{
		dir = env_my_get_env(info, "HOME=");
		if (!dir)
			chdir_return = 
				chdir((dir = env_my_get_env(info, "PWD=")) ? dir : "/");
		else
			chdir_return = chdir(dir);
	}
	else if (ut_strcmp(info->my_argv[1], "-") == 0)
	{
		if (!env_my_get_env(info, "OLDPWD="))
		{
			ut_puts(s);
			ut_putchar('\n');
			return (1);
		}
		ut_puts(env_my_get_env(info, "OLDPWD=")), ut_putchar('\n');
		chdir_return = 
			chdir((dir = env_my_get_env(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_return = chdir(info->my_argv[1]);
	if (chdir_return == -1)
	{
		eh_print_error(info, "can't cd to ");
		eh_eputs(info->my_argv[1]), eh_eputchar('\n');
	}
	else
	{
		_set_env(info, "OLDPWD", env_my_get_env(info, "PWD="));
		_set_env(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}


int pi_myhelp(my_arg_info *info)
{
	char **arg_array;

	arg_array = info->my_argv;
	ut_puts("help call works. Function not yet implemented \n");
	if (0)
		ut_puts(*arg_array);
	return (0);
}
