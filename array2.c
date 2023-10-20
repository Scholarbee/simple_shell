#include "sshell.h"


size_t arr_len(const list_tbl *head_ptr)
{
	size_t index = 0;

	while (head_ptr)
	{
		head_ptr = head_ptr->next;
		index++;
	}
	return (index);
}


char **arr_to_strings(list_tbl *head_ptr)
{
	list_tbl *ptr_node = head_ptr;
	size_t index = arr_len(head_ptr), e;
	char **strgs;
	char *s;

	if (!head_ptr || !index)
		return (NULL);
	strgs = malloc(sizeof(char *) * (index + 1));
	if (!strgs)
		return (NULL);
	for (index = 0; ptr_node; ptr_node = ptr_node->next, index++)
	{
		s = malloc(ut_strlen(ptr_node->p_str) + 1);
		if (!s)
		{
			for (e = 0; e < index; e++)
				free(strgs[e]);
			free(strgs);
			return (NULL);
		}

		s = ut_strcpy(s, ptr_node->p_str);
		strgs[index] = s;
	}
	strgs[index] = NULL;
	return (strgs);
}



size_t print_arr(const list_tbl *head_ptr)
{
	size_t index = 0;

	while (head_ptr)
	{
		ut_puts(eh_convert_number(head_ptr->num, 10, 0));
		ut_putchar(':');
		ut_putchar(' ');
		ut_puts(head_ptr->p_str ? head_ptr->p_str : "(nil)");
		ut_puts("\n");
		head_ptr = head_ptr->next;
		index++;
	}
	return (index);
}


list_tbl *arr_node_starts_with(list_tbl *ptr_node, char *prefx, char chr)
{
	char *ptr = NULL;

	while (ptr_node)
	{
		ptr = ut_starts_with(ptr_node->p_str, prefx);
		if (ptr && ((chr == -1) || (*ptr == chr)))
			return (ptr_node);
		ptr_node = ptr_node->next;
	}
	return (NULL);
}


ssize_t arr_get_node_index(list_tbl *head_ptr, list_tbl *ptr_node)
{
	size_t index = 0;

	while (head_ptr)
	{
		if (head_ptr == ptr_node)
			return (index);
		head_ptr = head_ptr->next;
		index++;
	}
	return (-1);
}
