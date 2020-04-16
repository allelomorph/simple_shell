/*
 * This file contains helper functions that manipulate strings.
 *
 * int _strlen(char *); - Determine the length of a string
 * char *_strdup(char *); - Duplicate a string to a new memory location
 * int _strcmp(char *, char *); - Compare two strings
 * char **str_arr_dup(char **); - Duplicate an array of strings to a new memory
 *         location
 * void str_arr_free(char **); - Free an array of char pointers
 */

#include "holberton.h"

/**
 * _strlen - counts char bytes in a string, not inlcuding null byte
 *
 *@s: string to be measured
 *
  * Return: int length of string
 */

int _strlen(char *s)
{
	int length = 0;

	for (; *s; s++)
	{
		length++;
	}
	return (length);
}

/**
 * _strdup - copies string into newly allocated memory
 *
 * @str: string to be copied
 *
 * Return: char pointer to new string
 */

char *_strdup(char *str)
{
	int size;
	int i;
	char *p = NULL;

	if (str == NULL)
		return (NULL);

	size = (_strlen(str) + 1);

	p = malloc(sizeof(char) * size);

	if (p == NULL)
	{
		perror("_strdup: malloc error");
		return (NULL);
	}
	for (i = 0; i < size; i++)
	{
		p[i] = str[i];
	}

	return (p);
}

/*	printf("_strdup: p malloc at %p\n", (void *)p); */

/**
 * _strcmp - compares two strings
 * @s1: pointer to the first string
 * @s2: pointer to the second string
 *
 * Return: the difference between the ASCII values of the first non-matching
 *         characters, 0 if they match
 */

int _strcmp(char *s1, char *s2)
{
	int idx, check = 0;

	if (!s1 && !s2)
		return (0);
	else if (!s1)
		return (0 - s2[0]);
	else if (!s2)
		return (s1[0]);

	for (idx = 0; s1[idx] && s2[idx] && !check; idx++)
	{
		if (s1[idx] != s2[idx])
			check = s1[idx] - s2[idx];
	}

	return (check);
}

/**
 * str_arr_dup - copies array of strings into newly allocated memory
 *
 * @array: array to be copied
 *
 * Return: char double pointer to new array
 */

char **str_arr_dup(char **array)
{
	char **copy = NULL;
	int strings, i, j;

	for (i = 0; array[i]; i++)
	{}
	strings = i;

	copy = malloc(sizeof(char *) * (strings + 1));

	if (!copy)
	{
		perror("str_arr_dup: malloc error");
		return (NULL);
	}

	for (i = 0; array[i]; i++)
	{
		copy[i] = _strdup(array[i]);
		if (!copy[i])
		{
			for (j = i; j > -1; j--)
			{
				perror("str_arr_dup: malloc error");
				free(copy[j]);
			}
			free(copy);
			return (NULL);
		}
	}
	copy[i] = NULL;
	return (copy);
}

/*
 * printf("str_arr_dup: copy malloc at %p\n", (void *)copy);
 * printf("str_arr_dup: copy free at %p\n", (void *)copy[j]);
 * printf("str_arr_dup: copy free at %p\n", (void *)copy);
*/

/**
 * str_arr_free - frees memory allocated to an array of char pointers
 *
 * @array: array, or char double pointer to be freed
 *
 * Return: none
 */

void str_arr_free(char **array)
{
	int i;

	if (array)
	{
		for (i = 0; array[i]; i++)
		{
			free(array[i]);
		}
		free(array);
	}
}

/*
 * printf("str_arr_free: array[i] free at %p\n", (void *)array[i]);
 * printf("str_arr_free: array free at %p\n", (void *)array);
*/
