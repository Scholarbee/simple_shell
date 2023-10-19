#include "sshell.h"

/**
 * ut_strlen - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */
int ut_strlen(char *str)
{
	int index = 0;

	if (!str)
		return (0);

	while (*str++)
		index++;
	return (index);
}

/**
 * ut_strcmp - performs lexicogarphic comparison of two strangs.
 * @str1: the first strang
 * @str2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int ut_strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * ut_starts_with - a function that checks if needle starts with haystack
 * @hystck: string to search
 * @ndle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *ut_starts_with(const char *hystck, const char *ndle)
{
	while (*ndle)
		if (*ndle++ != *hystck++)
			return (NULL);
	return ((char *)hystck);
}

/**
 * ut_strcat - a function that concatenates two strings
 * @dst: the destination buffer
 * @sc: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *ut_strcat(char *dst, char *sc)
{
	char *rt = dst;

	while (*dst)
		dst++;
	while (*sc)
		*dst++ = *sc++;
	*dst = *sc;
	return (rt);
}

