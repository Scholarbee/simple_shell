#include "sshell.h"

/**
 * mem_bfree - a function that frees a pointer and NULLs the address
 * @pointer: address of the pointer to be free
 *
 * Return: 1 if freed, if not 0.
 */
int mem_bfree(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
