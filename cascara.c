#include "holberton.h"

/**
 * _strncmp - compares a given amount of bytes between two strings
 *
 * @str1: first string to compare
 * @str2: second string to compare
 * @n: number of bytes to compare
 * Return: 0 on success (n bytes match), 1 on failure
 */

int _strncmp(char *str1, char *str2, unsigned int n)
{
	unsigned int i;

	if (!str1 || !str2)
		return (1);

	for (i = 0; i < n; i++)
	{
		if (str1[i] != str2[i])
			break;
	}

	if (i != n)
		return (1);

	return (0);
}

/**
 * run_command - checks validity of pathname before using child_exec to
 * fork and execute commmand
 * @av: string array of arguments
 * @my_env: copy of environmental variables
 * Return: 0 on success, 1 on general failure, 2 for command not found
 */

int run_command(char **av, char **my_env)
{
	char *abs_path = NULL;

	if (!av || !my_env)
		return (1);
/* first find the pathname using _which */
	abs_path = _which(av[0], my_env);
/* general _which failure */
	if (abs_path == NULL)
		return (1);
/* no valid pathname found for av[0], _which spits it back out unprocessed */
	if (abs_path == av[0])
	{
/* is it a valid executable not in the PATH? */
		if (access(abs_path, F_OK | X_OK) == 0)
		{
			if (execve(av[0], av, my_env) == -1)
			{
				perror("run_command: execve error");
				free(abs_path);
				return (1);
			}
		}
		else
		{
			perror(abs_path);
			return (2);
		}
	}
	else /* valid pathname created with _which, execute it */
	{
		if (execve(abs_path, av, my_env) == -1)
		{
			perror("run_command: execve error");
			free(abs_path);
			return (1);
		}
		free(abs_path);
	}
	return (0);
}

/*
 * printf("run_command: abs_path after which: %s\n", abs_path);
 * printf("run_command: abs_path free at %p\n", (void *)abs_path);
 *
 */

/**
 * shell_loop - primary user input loop, driven by loop_help functions.
 * takes user input stream from stdin and converts it to strings containing
 * arguments, to execute in the environment
 *
 * @my_env: malloc'd copy of environ passed from main
 * Return: 0 on success, -1 on failure
 */

int shell_loop(char **my_env)
{
	char *line = NULL, *exit_cmd = "exit", *env_cmd = "env";
	char **av = NULL;
	int ac = 0, flag = 0;

	do {
		line = get_input(my_env);
		if (!line)
			return (-1);
		if (line[0] == '\0') /* getline success, empty command line */
		{
			free(line);
			continue;
		}
		ac = count_tokens(line, " ");
		if (ac == -1)
			break;
		av = tokenize(line, ac, " ", flag);
		if (av == NULL)
			break;
		if (_strcmp(av[0], exit_cmd) == 0)
			break;
		if (_strcmp(av[0], env_cmd) == 0)
		{
			if (_env(my_env))
				break;
			free(av);
			free(line);
			continue;
		}
		if (child_exec(av, my_env, line))
			break;
		free(line);
	} while (line);
	free(av);
	free(line);
	return (0);
}

/*
 * printf("shell_loop: line free at %p\n", (void *)line);
 * do we need to build an array of structs with builtin names and
 * function pointers, just as with printf format tags?
 * then we could replace the manual checks for exit and env with one loop...
 */

/**
 * main - entry point
 *
 * Return: 0 on success, -1 on failure
 */

int main(void)
{
	char **my_env = NULL;

	int retval;

	my_env = str_arr_dup(environ);
	if (!my_env)
	{
		return (-1);
	}
	retval = shell_loop(my_env);

	str_arr_free(my_env);
	return (retval);
}
