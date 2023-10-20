#ifndef _SSHELL_H_
#define _SSHELL_H_

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/wait.h>


#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1


#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define HIST_FILE	".shell_history"
#define HIST_MAX	4096

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2


#define USE_GETLINE 0
#define USE_STRTOK 0


extern char **environ;


//edited
typedef struct list_str
{
	int num;
	char *p_str;
	struct list_str *next;
} list_tbl;


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

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}


typedef struct builtin
{
	char *type;
	int (*func)(arg_info *);
} builtin_table;


/* prtotype main_shell */
int ss_hsh(arg_info *, char **);
int ss_find_builtin(arg_info *);
void ss_find_cmd(arg_info *);
void ss_fork_cmd(arg_info *);

/* loophsh.c */
int ss_loophsh(char **);

/* prtotype for parse.c */
int parse_is_cmd(arg_info *, char *);
char *parse_dup_chars(char *, int, int);
char *parse_find_path(arg_info *, char *, char *);

/* prototype for handleErros1.c */
void eh_eputs(char *);
int eh_eputchar(char);
int eh_putfd(char c, int fd);
int eh_putsfd(char *str, int fd);

/* prototype for utils1.c */
int ut_strlen(char *);
int ut_strcmp(char *, char *);
char *ut_starts_with(const char *, const char *);
char *ut_strcat(char *, char *);

/* prototype for utils2.c */
char *ut_strcpy(char *, char *);
char *ut_strdup(const char *);
void ut_puts(char *);
int ut_putchar(char);

/* prototype for quit.c */
char *qt_strncpy(char *, char *, int);
char *qt_strncat(char *, char *, int);
char *qt_strchr(char *, char);
/* protype for parsers.c */
char **par_strtow(char *, char *);
char **par_strtow2(char *, char);

/* protype for alloc_again.c */
char *aa_memset(char *, char, unsigned int);
void aa_ffree(char **);
void *aa_realloc(void *, unsigned int, unsigned int);

/* mem.c */
int mem_bfree(void **);

/* prototype for converter.c */
int conv_interactive(arg_info *);
int conv_is_delim(char, char *);
int conv_isalpha(int);
int conv_atoi(char *);

/* prototype for handleErrors2.c */
int eh_erratoi(char *);
void eh_print_error(arg_info *, char *);
int eh_print_d(int, int);
char *eh_convert_number(long int, int, int);
void eh_remove_comments(char *);

/* prototype for plugin1.c */
int pi_myexit(arg_info *);
int pi_mycd(arg_info *);
int pi_myhelp(arg_info *);

/* prototype for plugin2.c */
int pi_myhistory(arg_info *);
int pi_myalias(arg_info *);

/* prototype for readInput.c */
ssize_t gInput(arg_info *);
int _gLine(arg_info *, char **, size_t *);
void sHandler(int);

/* prototype for readInfo.c */
void cInfo(arg_info *);
void sInfo(arg_info *, char **);
void fInfo(arg_info *, int);

/* prototype for env.c */
char *env_my_get_env(arg_info *, const char *);
int env_my_env(arg_info *);
int env_my_set_env(arg_info *);
int env_my_unset_env(arg_info *);
int env_populate_env_list(arg_info *);

/* prtotype for getEnv.c */
char **_get_env(arg_info *);
int _unset_env(arg_info *, char *);
int _set_env(arg_info *, char *, char *);

/* prototype for past.c */
char *get_past_file(arg_info *info);
int write_past(arg_info *info);
int read_past(arg_info *info);
int build_past_list(arg_info *info, char *buf, int linecount);
int renumber_past(arg_info *info);

/* prototype for array1.c */
list_t *arr_add_node(list_t **, const char *, int);
list_t *arr_add_node_end(list_t **, const char *, int);
size_t arr_print_list_str(const list_t *);
int arr_delete_node_at_index(list_t **, unsigned int);
void arr_free_list(list_t **);

/* prototype for array2.c */
size_t arr_len(const list_t *);
char **arr_to_strings(list_t *);
size_t print_arr(const list_t *);
list_t *arr_node_starts_with(list_t *, char *, char);
ssize_t arr_get_node_index(list_t *, list_t *);

/* prototype for var.c */
int var_is_chain(arg_info *, char *, size_t *);
void var_check_chain(arg_info *, char *, size_t *, size_t, size_t);
int var_replace_alias(arg_info *);
int var_replace_vars(arg_info *);
int var_replace_string(char **, char *);

#endif
