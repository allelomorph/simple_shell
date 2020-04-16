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

/*		if (fflush(stdin) != 0)
			perror("get_input: fflush error");
*/
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
