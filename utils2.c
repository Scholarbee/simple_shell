#include "sshell.h"

/**
 * ut_strcpy - a function that copies a string
 * @dst: the destination
 * @sc: the source
 *
 * Return: pointer to destination
 */
char *ut_strcpy(char *dst, char *sc)
{
	int index = 0;

	if (dst == sc || sc == 0)
		return (dst);
	while (sc[index])
	{
		dst[index] = sc[index];
		index++;
	}
	dst[index] = 0;
	return (dst);
}

/**
 * ut_strdup - a function that duplicates a string
 * @s: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *ut_strdup(const char *s)
{
	int len = 0;
	char *rt;

	if (s == NULL)
		return (NULL);
	while (*s++)
		len++;
	rt = malloc(sizeof(char) * (len + 1));
	if (!rt)
		return (NULL);
	for (len++; len--;)
		rt[len] = *--s;
	return (rt);
}

/**
 *ut_puts - a function that prints an input string
 *@s: the string to be printed
 *
 * Return: Nothing
 */
void ut_puts(char *s)
{
	int index = 0;

	if (!s)
		return;
	while (s[index] != '\0')
	{
		ut_putchar(s[index]);
		index++;
	}
}

/**
 * ut_putchar - a function that writes the character c to stdout
 * @chr: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int ut_putchar(char chr)
{
	static int index;
	static char bfer[WRITE_BUF_SIZE];

	if (chr == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(1, bfer, index);
		index = 0;
	}
	if (chr != BUF_FLUSH)
		bfer[index++] = chr;
	return (1);
}
