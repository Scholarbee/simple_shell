#include "sshell.h"


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


char *qt_strchr(char *str, char chr)
{
	do {
		if (*str == chr)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
