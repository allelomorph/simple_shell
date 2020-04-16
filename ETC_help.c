/*
 * This file contains additional helper functions for this program
 *
 * int _env(char **my_env); -- prints environment variables
 * int _putchar(char c) -- prints a single character to STDOUT
 * void _puts(char *c) -- uses _putchar to print a string
 */

#include "holberton.h"

/**
 * _env - prints all environmental (exported) variables for calling process
 * (stock env also takes variables as args, to set values)
 *
 * @my_env: array of strings containing environmental variables
 *
 * Return: 0 on success, 1 on fail
 */

int _env(char **my_env)
{
	int i;

	if (!my_env)
		return (1);

	for (i = 0; my_env[i]; i++)
	{
		_puts(my_env[i]);
		_putchar('\n');
	}

	return (0);
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _puts - print a string to stdout
 * @str: the string to print
 *
 * Return: void
 */

void _puts(char *str)
{
	int idx = 0;

	while (*(str + idx))
	{
		_putchar(*(str + idx));
		idx++;
	}
}
