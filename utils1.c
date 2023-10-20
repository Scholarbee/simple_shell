#include "sshell.h"


int ut_strlen(char *str)
{
	int index = 0;

	if (!str)
		return (0);

	while (*str++)
		index++;
	return (index);
}


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


char *ut_starts_with(const char *hystck, const char *ndle)
{
	while (*ndle)
		if (*ndle++ != *hystck++)
			return (NULL);
	return ((char *)hystck);
}


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

