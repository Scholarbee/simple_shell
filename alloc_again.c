 #include "sshell.h"

/**
 **aa_memset - a function that fills memory with a constant byte
 *@ptr_s: the pointer to the memory area
 *@byte_b: the byte to fill *s with
 *@n: the number of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *aa_memset(char *ptr_s, char byte_b, unsigned int n)
{
	unsigned int index;

	for (index = 0; index < n; index++)
		ptr_s[index] = byte_b;
	return (ptr_s);
}

/**
 * aa_ffree - a function that frees an array of strings
 * @ss: an array of strings
 */
void aa_ffree(char **ss)
{
	char **ptr_a = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);
	free(ptr_a);
}

/**
 * aa_realloc - a function that allocates a block of memory again
 * @prev_ptr: pointer to previous malloc'ated block
 * @old_byte: byte/size size of previous block
 * @new_byte: byte/size size of new block
 *
 * Return: pointer to the old block-ed memory.
 */
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
