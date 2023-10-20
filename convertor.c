#include "sshell.h"


int conv_interactive(arg_info *ptr_info)
{
	return (isatty(STDIN_FILENO) && ptr_info->readfd <= 2);
}


int conv_is_delim(char chr, char *delm)
{
	while (*delm)
		if (*delm++ == chr)
			return (1);
	return (0);
}



int conv_isalpha(int chr)
{
	if ((chr >= 'a' && chr <= 'z') || (chr >= 'A' && chr <= 'Z'))
		return (1);
	else
		return (0);
}



int conv_atoi(char *str)
{
	int index, sgn = 1, flg = 0, op;
	unsigned int reslt = 0;

	for (index = 0;  str[index] != '\0' && flg != 2; index++)
	{
		if (str[index] == '-')
			sgn *= -1;

		if (str[index] >= '0' && str[index] <= '9')
		{
			flg = 1;
			reslt *= 10;
			reslt += (str[index] - '0');
		}
		else if (flg == 1)
			flg = 2;
	}

	if (sgn == -1)
		op = -reslt;
	else
		op = reslt;

	return (op);
}
