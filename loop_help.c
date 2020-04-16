/*
 * This file contains helper functions that process user input.
 *
 * char *get_input(void); - get user input from standard input
 * int count_tokens(char *, char *); - count sub-strings defined by a delimiter
 * char **tokenize(char *, int, char *); - separate sub-strings defined by a
 *         delimiter
 * int child_exec(char *, char **, char **); - execute command in a child
 *         process
 */

#include "holberton.h"

/**
 * get_input - takes user input from sdtin stream and converts to a string
 *
 * @my_env: malloc'd copy of environ
 *
 * Return: char pointer to string containing user input
 */

char *get_input(char **my_env)
{
	char *input = NULL; /* init or valgrind error */
	ssize_t read_bytes = 0;
	size_t buf_bytes = 0; /* must be intialized or segfault on getline */

	if (isatty(STDIN_FILENO) == 1)
/* input is from stdin, in interactive mode */
		_puts("Cascara $ ");
	else if (errno != ENOTTY)
		perror("get_input: isatty error");

	read_bytes = getline(&input, &buf_bytes, stdin);

	if (read_bytes == -1)
	{
		if (errno == 0)
		{
			_puts("exit\n");
			free(input);
			str_arr_free(my_env);
			exit(EXIT_SUCCESS);
		}
/* ENOTTY: getline errno after last line in non-interactive mode input */
		else if (errno != ENOTTY)
			perror("get_input: getline error");

		free(input);

		if (fflush(stdin) != 0)
			perror("get_input: fflush error");

		return (NULL);
	}
	input[read_bytes - 1] = '\0'; /* remove newline char from input */

	return (input);
}

/*
 * printf("get_input: input malloc at %p\n", (void *)input);
 * printf("get_input: input free at %p\n", (void *)input);
 * printf("getline errno: %i\n", errno);
 *	if (fflush(stdin) != 0)
 *	{
 *		perror("get_input: fflush error");
 *		return (NULL);
 *		}
 */

/**
 * count_tokens - parses a string to count sub-strings separated by
 * a given delimiter
 *
 * @input: string to parse
 *
 * @delim: delimiter char or string
 *
 * Return: int counting the number of delimited sub-strings, or -1 on failure
 */

int count_tokens(char *input, char *delim)
{
	char *temp_buf = NULL, *token = NULL;
	int ac;

	if (!input || !delim)
		return (-1);

	temp_buf = _strdup(input);

	if (!temp_buf)
	{
		return (-1);
	}

	token = strtok(temp_buf, delim);

	if (!token)
	{
		free(temp_buf);
		perror("count_tokens: strtok error");
		return (-1);
	}

	for (ac = 0; token; ac++)
	{
		token = strtok(NULL, delim);
/* strtok has no errno output, and returning NULL is needed to end the loop */
	}
	free(temp_buf);
	return (ac);
}

/*
 * printf("count_tokens: temp_buf malloc at %p\n", (void *)temp_buf);
 * printf("count_tokens: temp_buf free at %p\n", (void *)temp_buf);
 */

/**
 * tokenize - parses a string to return pointers to sub-strings separated by
 * a given delimiter
 *
 * @input: string to parse
 *
 * @ac: amount of expected sub-strings
 *
 * @delim: delimiter char or string
 *
 * @flag: 0 = normal operation, 1 = av[0] intentional placeholder string
 *
 * Return: pointer to an array containing char pointers to positions
 * in input string.
 */

char **tokenize(char *input, int ac, char *delim, int flag)
{
	char **av = NULL;
	int i;

	if (flag)
		ac++;
	av = malloc(sizeof(char *) * (ac + 1));
	if (!av)
	{
		perror("tokenize: malloc error");
		return (NULL);
	}
	for (i = 0; i < ac; i++)
	{
		if (flag)
		{
			if (i == 0)
				av[i] = ".";
			else if (i == 1)
				av[i] = strtok(input, delim);
			else
				av[i] = strtok(NULL, delim);
		}
		else if (i == 0)
		{
			av[i] = strtok(input, delim);
			if (!av[i]) /* no mention of errno in strtok man page */
				return (NULL);
		}
		else
		{
			av[i] = strtok(NULL, delim);
			if (!av[i]) /* no mention of errno in strtok man page */
				return (NULL);
		}
	}
	av[ac] = NULL;
	return (av);
}

/*	printf("tokenize: av malloc at %p\n", (void *)av); */

/**
 * child_exec - forks into child process to execute command in user input
 * with given args and environment
 *
 * @argv: array of args as strings
 *
 * @env: array of evironmental variables as strings
 *
 * @line: getline input from get_input()
 *
 * Return: 0 on success, 1 on failure
 */

int child_exec(char **argv, char **env, char *line)
{
	pid_t pid;
	int status, rc_retval;

	pid = fork();
	if (pid == -1)
	{
		perror("child_exec: fork error");
		free(argv);
		return (1);
	}
	if (pid == 0)
	{
		rc_retval = run_command(argv, env);
		if (rc_retval)
		{
			if (rc_retval == 1)
				return (1);
			free(argv);
			free(line);
			str_arr_free(env);
			_exit(127);
		}
	}
	else
	{
		wait(&status);
		free(argv);
	}

	return (0);
}

/*
 * printf("chlid_exec: argv free at %p\n", (void *)argv);
 * printf("chlid_exec(child): argv free at %p\n", (void *)argv);
 * printf("chlid_exec(parent): argv free at %p\n", (void *)argv);
 * printf("run_command: av free at %p\n", (void *)av);
 * running execve on setenv + unsetenv with helpers arr_to_nodes
 * and nodes_to_arr could modify my_env for future loops
 * perror status?
 */
