#include "sshell.h"

/**
 * conv_interactive - a function that returns true if shell is interactive mode
 * @ptr_info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int conv_interactive(arg_info *ptr_info)
{
	return (isatty(STDIN_FILENO) && ptr_info->readfd <= 2);
}

/**
 * conv_is_delim - a function that checks if character is a delimeter
 * @chr: the character to check
 * @delm: the delimeter string
 * Return: 1 on success, 0 on failure
 */
int conv_is_delim(char chr, char *delm)
{
	while (*delm)
		if (*delm++ == chr)
			return (1);
	return (0);
}

/**
 *conv_isalpha - a function that checks for alphabetic character
 *@chr: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int conv_isalpha(int chr)
{
	if ((chr >= 'a' && chr <= 'z') || (chr >= 'A' && chr <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *conv_atoi - a function that converts a string to an integer
 *@str: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

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
