#include "sshell.h"


list_t *arr_add_node(list_t **head_ptr, const char *str, int nb)
{
	list_t *new_head;

	if (!head_ptr)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	aa_memset((void *)new_head, 0, sizeof(list_t));
	new_head->n = nb;
	if (str)
	{
		new_head->str = ut_strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head_ptr;
	*head_ptr = new_head;
	return (new_head);
}


list_t *arr_add_node_end(list_t **head_ptr, const char *str, int nb)
{
	list_t *new_node, *node;

	if (!head_ptr)
		return (NULL);

	node = *head_ptr;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	aa_memset((void *)new_node, 0, sizeof(list_t));
	new_node->n = nb;
	if (str)
	{
		new_node->str = ut_strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head_ptr = new_node;
	return (new_node);
}


size_t arr_print_list_str(const list_t *head_ptr)
{
	size_t i = 0;

	while (head_ptr)
	{
		ut_puts(head_ptr->str ? head_ptr->str : "(nil)");
		ut_puts("\n");
		head_ptr = head_ptr->next;
		i++;
	}
	return (i);
}


int arr_delete_node_at_index(list_t **head_ptr, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head_ptr || !*head_ptr)
		return (0);

	if (!index)
	{
		node = *head_ptr;
		*head_ptr = (*head_ptr)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head_ptr;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}


void arr_free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
