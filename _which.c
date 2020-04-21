#include "holberton.h"

/**
 * test_path - subroutine for _which, searches through string array paths,
 * concatenating paths[i] with '/' + func, and testing it for accessibility
 *
 * @func: name of program
 *
 * @paths: previously allocated array of colon delimited paths in PATH
 *
 * Return: string containing full valid path of executable, func if none found,
 * or NULL on failure
 */

char *test_path(char **paths, char *func)
{
	int arg_len, path_len, test_len, i, j;
	char *test;

	if (!paths || !func)
		return (NULL);
/* for each string in paths, create temp = ccat of paths[i] + "/func" */
	arg_len = _strlen(func);
	for (i = 0; paths[i]; i++)
	{
		path_len = _strlen(paths[i]);
		test_len = (path_len + arg_len) + 2;
		test = malloc(sizeof(char) * test_len);
		if (!test)
		{
			perror("test_path: malloc error");
			return (NULL);
		}
		for (j = 0; j < test_len; j++)
		{
			if (j < path_len)
				test[j] = paths[i][j];
			else if (j == path_len)
				test[j] = '/';
			else if (j > path_len && j < test_len)
				test[j] = func[j - (path_len + 1)];
			else if (j == test_len - 1)
				test[j] = '\0';
		}
/* if temp is accessible and executable, stop search to return it */
		if (access(test, F_OK | X_OK) == 0)
			return (test);
		if (errno != ENOENT)
			perror("test_path: access error");
		free(test);
	}
	return (func);
}

/*
 * printf("test_path: malloc at %p\n", (void *)test)
 * printf("test_path: free test at %p test:%s\n", (void *)test, test);
 * printf("paths[%i]: test: %s\n", i, test);
 * printf("paths[%i]: %s test : %s\n", i, paths [i], test);
 * printf("paths[%i]: %s j: %i test: %s\n", i, paths[i], j, test);
 *
 */

/**
 * get_PATH_dir - tokenizes PATH value into separate directory pathnames
 * @env_var: copy of the PATH variable from my_env
 *
 * Return: array of char pointers to directory pathnames
 */

char **get_PATH_dir(char *env_var)
{
	char *value;
	char **paths;
	int path_ct, flag = 0;

	if (!env_var)
		return (NULL);
	value = strtok(env_var, "=");
	if (!value) /* tokenize env_var for value, colon delim value of PATH */
	{
		free(env_var);
		perror("get_PATH_dir: 1st strtok error");
		return (NULL);
	}
	value = strtok(NULL, "=");
	if (!value)
	{
		if (errno != ENOTTY)
		{
			free(env_var);
			perror("get_PATH_dir: 2nd strtok error");
		}
		return (NULL);
	}
	path_ct = count_tokens(value, ":");
	if (path_ct == -1)
	{
		free(env_var);
		return (NULL);
	}
	if (value[0] == ':')
		flag = 1; /* empty path first member of paths, use pwd */
	paths = tokenize(value, path_ct, ":", flag);
	if (!paths)
	{
		free(env_var);
		return (NULL);
	}
	return (paths);
}

/*
 *	for (i = 0; paths[i]; i++)
 *	{
 *		printf("paths[%i]: %s\n", i, paths[i]);
 *	}
 *
 *      printf("_which: env_var free at %p\n", (void *)env_var);
 */



/**
 * _which - returns full valid pathname for the executable file named
 * as argument, found by searching through all colon delimted paths in PATH
 *
 * @func: name of program
 *
 * @my_env: previously allocated copy of parent process' environ array
 *
 * Return: string containing full valid path of executable, original
 * av[0] if none found, or NULL on failure
 */

char *_which(char *func, char **my_env)
{
	char *pth = NULL, *pwd = NULL, *test = NULL;
	char **paths = NULL;
	int i;

	if (!func)
		return (NULL);
	for (i = 0; my_env[i]; i++) /* search, get copies of PATH and PWD */
	{
		if (_strncmp(my_env[i], "PATH=", 5) == 0)
			pth = _strdup(my_env[i]);
		if (_strncmp(my_env[i], "PWD=", 4) == 0)
			pwd = _strdup(my_env[i]);
	}
	if (!pth || !pwd || pth[5] == '\0')
/* "PATH=", empty path, return unmodifed func */
	{
		if (pth)
			free(pth);
		if (pwd)
			free(pwd);
		return (func);
	} /* separate PATH from its value, and then that value into paths */
	paths = get_PATH_dir(pth);
	if (!paths) /* env_var already freed in all failure cases of gPd */
		return (NULL);
	if (paths[0][0] == '.')
	{
		paths[0] = strtok(pwd, "=");
		paths[0] = strtok(NULL, "=");
	} /* returns valid path from paths[i] + "/func", or func if none */
	test = test_path(paths, func);
	free(paths); /* cleanup */
	free(pth);
	free(pwd);
	if (!test)
		return (NULL);
	return (test);
}

/*
 * printf("_which: paths free at %p\n", (void *)paths);
 * printf("_which: env_var free at %p\n", (void *)env_var);
 * notes:
 * stock which return: 0 if commands are found and executable,
 * 1 if not found or executable, 2 if invalid option specified
 *
 * stock which takes variable args, and returns path for each
 */
