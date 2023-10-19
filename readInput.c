#include "sshell.h"

/**
 * input_buffer - a function that buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @length: address of length var
 *
 * Return: bytes read
 */
ssize_t input_buffer(arg_info *info, char **buf, size_t *length)
{
	ssize_t r = 0;
	size_t len_p = 0;

	/* if nothing left in the buffer, fill it */
	if (!*length)
	{
		/*bfree((void **)info->cmd_buf);*/
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
				/* remove trailing newline */
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->lc_flag = 1;
			eh_remove_comments(*buf);
			build_past_list(info, *buf, info->history_number++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*length = r;
				info->commandBuffer = buf;
			}
		}
	}
	return (r);
}

/**
 * gInput - a function that gets a line without the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t gInput(arg_info *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	ut_putchar(BUF_FLUSH);
	r = input_buffer(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		var_check_chain(info, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (var_is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			info->commandBufferType = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (ut_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
}

/**
 * read_buffer - a function that reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @size: size
 *
 * Return: r
 */
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

/**
 * _gLine - a function that gets the next line of input from STDIN
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @info: parameter struct
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
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
	if (!new_p) /* MALLOC FAILURE! */
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

/**
 * sHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sHandler(__attribute__((unused))int sig_num)
{
	ut_puts("\n");
	ut_puts("$ ");
	ut_putchar(BUF_FLUSH);
}
