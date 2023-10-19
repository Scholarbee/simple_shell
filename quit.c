#include "sshell.h"

/**
 **qt_strncpy - a function that copies a string
 *@dst: the destination string to be copied to
 *@sc: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *qt_strncpy(char *dst, char *sc, int n)
{
	int index, e;
	char *s = dst;

	index = 0;
	while (sc[index] != '\0' && index < n - 1)
	{
		dst[index] = sc[index];
		index++;
	}
	if (index < n)
	{
		e = index;
		while (e < n)
		{
			dst[e] = '\0';
			e++;
		}
	}
	return (s);
}

/**
 **qt_strncat - a function that concatenates two strings
 *@dst: the first string
 *@sc: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *qt_strncat(char *dst, char *sc, int n)
{
	int index, e;
	char *s = dst;

	index = 0;
	e = 0;
	while (dst[index] != '\0')
		index++;
	while (sc[e] != '\0' && e < n)
	{
		dst[index] = sc[e];
		index++;
		e++;
	}
	if (e < n)
		dst[index] = '\0';
	return (s);
}

/**
 **qt_strchr - a function that locates a character in a string
 *@str: the string to be parsed
 *@chr: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *qt_strchr(char *str, char chr)
{
	do {
		if (*str == chr)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
