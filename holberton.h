#ifndef HOLBERTON_H
#define HOLBERTON_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

/* C standard library global variables */
extern int errno;
/* extern char **environ; */

/* cascara.c */
int _strncmp(char *str1, char *str2, unsigned int n);
int run_command(char **av, char **my_env);
int shell_loop(char **my_env, char *main);

/* string_help.c */
int _strlen(char *s);
char *_strdup(char *str);
int _strcmp(char *s1, char *s2);
char **str_arr_dup(char **array);
void str_arr_free(char **array);

/* loop_help.c */
char *get_input(char **av, char **my_env, int ce_retval);
int count_tokens(char *input, char *delim);
char **tokenize(char *input, int ac, char *delim, int flag);
int child_exec(char **argv, char **env, char *main, int loop, char *line);

/* ETC_help.c */
int _env(char **my_env);
int _putchar(char c);
void _puts(char *str);
void puts_err(char *main_arg, int loop, char *func);
char *uns_itoa(unsigned int dec);

/* _which.c */
char *test_path(char **paths, char *func);
char **get_PATH_dir(char *env_var);
char *_which(char *func, char **my_env);

/* (future implementations) ?env_help.c? */
char *_getenv(const char *name);
int _setenv(const char *name, const char *value, int overwrite);
int unsetenv(const char *name);

/**
 * struct path_n - colon delimited strings from env var PATH as linked list
 * @path: path name
 * @next: pointer to next path_n struct
 *
 * Description: for conversion of PATH variable value into linked list of paths
 */
typedef struct path_n
{
	char *path;
	struct path_n *next;
} path_node;

/**
 * struct env_var - environmental variables as linked list
 * @v_name: variable name as string
 * @v_val: variable value as string
 * @next: pointer to next env_var struct
 *
 * Description: for conversion of array of environmental variables
 * into a linked list to facilitate editing
 */
typedef struct env_var
{
	char *v_name;
	char *v_val;
	struct env_var *next;
} env_node;

#endif /* HOLBERTON_H */
