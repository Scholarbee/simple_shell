#include "sshell.h"

/**
 *eh_eputs - a function that prints an input string
 * @s: the string to be printed
 *
 * Return: Nothing
 */
void eh_eputs(char *s)
{
	int index = 0;

	if (!s)
		return;
	while (s[index] != '\0')
	{
		eh_eputchar(s[index]);
		index++;
	}
}

/**
 * eh_eputchar - a function that writes the character c to stderr
 * @chr: The character to writes
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set.
 */
int eh_eputchar(char chr)
{
	static int index;
	static char bfer[WRITE_BUF_SIZE];

	if (chr == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(2, bfer, index);
		index = 0;
	}
	if (chr != BUF_FLUSH)
		bfer[index++] = chr;
	return (1);
}

/**
 * eh_putfd - a function that writes the character c to given file descriptor
 * @chr: The character to write
 * @fdsc: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set.
 */
int eh_putfd(char chr, int fdsc)
{
	static int index;
	static char bfer[WRITE_BUF_SIZE];

	if (chr == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(fdsc, bfer, index);
		index = 0;
	}
	if (chr != BUF_FLUSH)
		bfer[index++] = chr;
	return (1);
}

/**
 *eh_putsfd - a function that prints an input string
 * @s: the string to be written
 * @fdsc: the file descriptor to write to
 *
 * Return: the number of chars put
 */
int eh_putsfd(char *s, int fdsc)
{
	int index = 0;

	if (!s)
		return (0);
	while (*s)
	{
		index += eh_putfd(*s++, fdsc);
	}
	return (index);
}
