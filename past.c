#include "sshell.h"

/**
 * get_past_file - a function that gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_past_file(arg_info *info)
{
	char *buf, *directory;

	directory = env_my_get_env(info, "HOME=");
	if (!directory)
		return (NULL);
	buf = malloc(sizeof(char) * (ut_strlen(directory) + ut_strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	ut_strcpy(buf, directory);
	ut_strcat(buf, "/");
	ut_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_past - a function that creates a file, or add to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_past(arg_info *info)
{
	ssize_t fd;
	char *filename = get_past_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		eh_putsfd(node->str, fd);
		eh_putfd('\n', fd);
	}
	eh_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_past - a function that reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_past(arg_info *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, readlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_past_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	readlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (readlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_past_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_past_list(info, buf + last, linecount++);
	free(buf);
	info->history_number = linecount;
	while (info->history_number-- >= HIST_MAX)
		arr_delete_node_at_index(&(info->history), 0);
	renumber_past(info);
	return (info->history_number);
}

/**
 * build_past_list - a function that adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, history_number
 *
 * Return: Always 0
 */
int build_past_list(arg_info *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	arr_add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_past - a function that renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_past(arg_info *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->n = i++;
		node = node->next;
	}
	return (info->history_number = i);
}
