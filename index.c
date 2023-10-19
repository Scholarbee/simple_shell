#include "sshell.h"

/**
 * main - entry point
 * @ac: parameter as arg count
 * @av: parameter as arg vector
 *
 * Return: 0 on success, 1 on failure
 */
int main(int a, char **v)
{
	arg_info info[] = { INFO_INIT };
	int fdsc = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fdsc)
		: "r" (fdsc));

	if (a == 2)
	{
		fdsc = open(v[1], O_RDONLY);
		if (fdsc == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				eh_eputs(v[0]);
				eh_eputs(": 0: Can't open ");
				eh_eputs(v[1]);
				eh_eputchar('\n');
				eh_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fdsc;
	}
	env_populate_env_list(info);
	read_past(info);
	ss_hsh(info, v);
	return (EXIT_SUCCESS);
}
