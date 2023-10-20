#include "sshell.h"


int parse_is_cmd(arg_info *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}


char *parse_dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}


char *parse_find_path(arg_info *info, char *path_string, char *command)
{
	int i = 0, current_position = 0;
	char *path;

	if (!path_string)
		return (NULL);
	if ((ut_strlen(command) > 2) && ut_starts_with(command, "./"))
	{
		if (parse_is_cmd(info, command))
			return (command);
	}
	while (1)
	{
		if (!path_string[i] || path_string[i] == ':')
		{
			path = parse_dup_chars(path_string, current_position, i);
			if (!*path)
				ut_strcat(path, command);
			else
			{
				ut_strcat(path, "/");
				ut_strcat(path, command);
			}
			if (parse_is_cmd(info, path))
				return (path);
			if (!path_string[i])
				break;
			current_position = i;
		}
		i++;
	}
	return (NULL);
}
