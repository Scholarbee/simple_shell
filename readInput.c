#include "sshell.h"


ssize_t input_buffer(my_arg_info *ptr_info, char **bfer, size_t *length)
{
	ssize_t r = 0;
	size_t len_p = 0;

	
	if (!*length)
	{
		
		free(*bfer);
		*bfer = NULL;
		signal(SIGINT, sHandler);
#if USE_GETLINE
		r = _gLine(bfer, &len_p, stdin);
#else
		r = _gLine(ptr_info, bfer, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				
				(*buf)[r - 1] = '\0';
				r--;
			}
			ptr_info->my_lc_flag = 1;
			eh_remove_comments(*bfer);
			build_past_list(info, *buf, info->my_history_number++);
			
			{
				*length = r;
				info->my_commandBuffer = bfer;
			}
		}
	}
	return (r);
}


ssize_t gInput(my_arg_info *ptr_info)
{
	static char *bfer; 
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(ptr_info->my_arg), *p;

	ut_putchar(BUF_FLUSH);
	r = input_buffer(ptr_info, &bfer, &len);
	if (r == -1) 
		return (-1);
	if (len)
	{
		j = i;
		p = bfer + i;

		var_check_chain(ptr_info, bfer, &j, i, len);
		while (j < len)
		{
			if (var_is_chain(ptr_info, bfer, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			ptr_info->my_commandBufferType = CMD_NORM;
		}

		*buf_p = p;
		return (ut_strlen(p));
	}

	*buf_p = buf;
	return (r);
}


ssize_t read_buffer(my_arg_info *ptr_info, char *buf, size_t *size)
{
	ssize_t r = 0;

	if (*size)
		return (0);
	r = read(ptr_info->my_readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*size = r;
	return (r);
}


int _gLine(my_arg_info *ptr_info, char **ptr, size_t *length)
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

	r = read_buffer(ptr_info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = qt_strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = aa_realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		qt_strncat(new_p, bfer + i, k - i);
	else
		qt_strncpy(new_p, bfer + i, k - i + 1);

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
