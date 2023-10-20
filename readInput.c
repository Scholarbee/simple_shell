#include "sshell.h"


ssize_t input_buffer(arg_info *info, char **buf, size_t *length)
{
	ssize_t r = 0;
	size_t len_p = 0;

	
	if (!*length)
	{
		
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sHandler);
#if USE_GETLINE
		r = _gLine(buf, &len_p, stdin);
#else
		r = _gLine(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->lc_flag = 1;
			eh_remove_comments(*buf);
			build_past_list(info, *buf, info->history_number++);
			
			{
				*length = r;
				info->commandBuffer = buf;
			}
		}
	}
	return (r);
}


ssize_t gInput(arg_info *info)
{
	static char *buf; 
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	ut_putchar(BUF_FLUSH);
	r = input_buffer(info, &buf, &len);
	if (r == -1) 
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		var_check_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (var_is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->commandBufferType = CMD_NORM;
		}

		*buf_p = p;
		return (ut_strlen(p));
	}

	*buf_p = buf;
	return (r);
}


ssize_t read_buffer(arg_info *info, char *buf, size_t *size)
{
	ssize_t r = 0;

	if (*size)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*size = r;
	return (r);
}


int _gLine(arg_info *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buffer(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = qt_strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = aa_realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		qt_strncat(new_p, buf + i, k - i);
	else
		qt_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}


void sHandler(__attribute__((unused))int sig_num)
{
	ut_puts("\n");
	ut_puts("$ ");
	ut_putchar(BUF_FLUSH);
}
