#include "sshell.h"

typedef struct builtin
{
	char *type;
	int (*func)(arg_info *);
} builtin_table;


typedef struct liststr
{
	int n;
	char *str;
	struct liststr *next;
} list_t;


typedef struct argument_passed
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int count_line;
	int err_num;
	
	int lc_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **commandBuffer;
	int commandBufferType;
	int readfd;
	int history_number;
} arg_info;