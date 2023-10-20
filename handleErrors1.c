#include "sshell.h"


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
