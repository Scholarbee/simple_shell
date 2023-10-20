 #include "sshell.h"


char *aa_memset(char *ptr_s, char byte_b, unsigned int n)
{
	unsigned int index;

	for (index = 0; index < n; index++)
		ptr_s[index] = byte_b;
	return (ptr_s);
}


void aa_ffree(char **ss)
{
	char **ptr_a = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);
	free(ptr_a);
}


void *aa_realloc(void *prev_ptr, unsigned int old_byte, unsigned int new_byte)
{
	char *prt_p;

	if (!prev_ptr)
		return (malloc(new_byte));
	if (!new_byte)
		return (free(prev_ptr), NULL);
	if (new_byte == old_byte)
		return (prev_ptr);

	prt_p = malloc(new_byte);
	if (!prt_p)
		return (NULL);

	old_byte = old_byte < new_byte ? old_byte : new_byte;
	while (old_byte--)
		prt_p[old_byte] = ((char *)prev_ptr)[old_byte];
	free(prev_ptr);
	return (prt_p);
}
