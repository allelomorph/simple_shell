/*
 * This file contains additional helper functions for this program
 *
 * int _env(char **my_env); -- prints environment variables
 * int _putchar(char c) -- prints a single character to STDOUT
 * void _puts(char *c) -- uses _putchar to print a string
 * void puts_err - prints custom message to stderr
 * char *uns_itoa - converts unsigned integers to strings
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


/**
 * puts_err - prints custom message to stderr
 * @main_arg: av[0] to main itself, not getline input
 * @loop: getline input cycle incrementor
 * @func: av[0] from getline input
 * Return: void
 */

void puts_err(char *main_arg, int loop, char *func)
{
	int main_len, func_len, inc_len;
	char *delim = ": ", *loop_inc = NULL;

	main_len = _strlen(main_arg);
	func_len = _strlen(func);
	loop_inc = uns_itoa(loop);
	inc_len = _strlen(loop_inc);
/* "./[exe]: " */
	write(2, main_arg, main_len);
	write(2, delim, 2);
/* "[loop_inc]: " */
	write(2, loop_inc, inc_len);
	write(2, delim, 2);
/* "[func]: " */
	write(2, func, func_len);
	write(2, delim, 2);

	free(loop_inc);
}

/**
 * uns_itoa - converts unsigned integers to strings
 * @dec: unsigned int to convert
 * Return: string of numerals representing value
 */

char *uns_itoa(unsigned int dec)
{
	char *uns;
	unsigned int pow_10 = 1;
	int count = 1;
	int i;

	while (pow_10 <= (dec / 10))
	{
		pow_10 *= 10;
		count++;
	}
	uns = malloc(sizeof(char) * (count + 1));

	if (!uns)
	{
		free(uns);
		return (NULL);
	}
	for (i = 0; i < count; i++)
	{
		uns[i] = ((dec / pow_10) + '0');
		dec %= pow_10;
		pow_10 /= 10;
	}
	uns[i] = '\0';

	return (uns);
}
/*  UINT_MAX = 4294967296 or 1111 1111 1111 1111 1111 1111 1111 1111 */
