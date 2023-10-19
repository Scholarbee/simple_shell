#include "sshell.h"

/**
 * eh_erratoi - a function that converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int eh_erratoi(char *str)
{
	int index = 0;
	unsigned long int r = 0;

	if (*str == '+')
		str++;  
	for (index = 0;  str[index] != '\0'; index++)
	{
		if (str[index] >= '0' && str[index] <= '9')
		{
			r *= 10;
			r += (str[index] - '0');
			if (r > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (r);
}

/**
 * eh_print_error - a function that prints an error message
 * @ptr_info: the parameter & return info struct
 * @s: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void eh_print_error(arg_info *ptr_info, char *s)
{
	eh_eputs(ptr_info->fname);
	eh_eputs(": ");
	eh_print_d(ptr_info->count_line, STDERR_FILENO);
	eh_eputs(": ");
	eh_eputs(ptr_info->argv[0]);
	eh_eputs(": ");
	eh_eputs(s);
}

/**
 * eh_print_d - function prints a decimal (integer) number (base 10)
 * @inpt: the input
 * @fdsc: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int eh_print_d(int inpt, int fdsc)
{
	int (*__putchar)(char) = ut_putchar;
	int index, c = 0;
	unsigned int _abs_, cur;

	if (fdsc == STDERR_FILENO)
		__putchar = eh_eputchar;
	if (inpt < 0)
	{
		_abs_ = -inpt;
		__putchar('-');
		c++;
	}
	else
		_abs_ = inpt;
	cur = _abs_;
	for (index = 1000000000; index > 1; index /= 10)
	{
		if (_abs_ / index)
		{
			__putchar('0' + cur / index);
			c++;
		}
		cur %= index;
	}
	__putchar('0' + cur);
	c++;

	return (c);
}

/**
 * eh_convert_number - converter function, a clone of itoa
 * @nb: number
 * @base: base
 * @flgs: argument flags
 *
 * Return: string
 */
char *eh_convert_number(long int nb, int b, int flgs)
{
	static char *arr;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = nb;

	if (!(flgs & CONVERT_UNSIGNED) && nb < 0)
	{
		n = -nb;
		sign = '-';

	}
	arr = flgs & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = arr[n % b];
		n /= b;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * eh_remove_comments - function replaces first chance of '#' with '\0'
 * @bfer: address of the string to change
 *
 * Return: Always 0;
 */
void eh_remove_comments(char *bfer)
{
	int index;

	for (index = 0; bfer[index] != '\0'; index++)
		if (bfer[index] == '#' && (!index || bfer[index - 1] == ' '))
		{
			bfer[index] = '\0';
			break;
		}
}
