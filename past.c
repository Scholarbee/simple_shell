#include "sshell.h"



char *get_past_file(my_arg_info *info)
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


int write_past(my_arg_info *info)
{
	ssize_t fd;
	char *filename = get_past_file(info);
	list_tbl *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		eh_putsfd(node->p_str, fd);
		eh_putfd('\n', fd);
	}
	eh_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}


int read_past(my_arg_info *info)
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


int build_past_list(my_arg_info *info, char *buf, int linecount)
{
	list_tbl *node = NULL;

	if (info->history)
		node = info->history;
	arr_add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}


int renumber_past(my_arg_info *info)
{
	list_tbl *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->history_number = i);
}
