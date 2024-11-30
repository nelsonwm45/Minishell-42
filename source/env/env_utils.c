/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:15:26 by nchok             #+#    #+#             */
/*   Updated: 2024/11/26 17:15:26 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/*
@brief : Retrieves the current working directory (PWD) from the environment 
			variables and stores it in utils->pwd.

1. Loops through the environment variables array utils->envp to find the entry 
	starting with "PWD=".
2. If found, sets utils->pwd to point to this entry and returns 0 (success).
3. If not found, writes "PWD not found\n" to standard error and exits the 
	program with an error status.
*/
int	get_pwd(t_general *utils)
{
	int	i;

	i = 0;
	while (utils->envp[i] != NULL)
	{
		if (ft_strncmp(utils->envp[i], "PWD=", 4) == 0)
		{
			utils->pwd = utils->envp[i];
			return (0);
		}
		i++;
	}
	if (utils->envp[i] == NULL)
	{
		ft_putstr_fd("PWD not found\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	return (ERROR);
}

/*
@brief : Retrieves the previous working directory (OLDPWD) from 
		the environment variables and stores it in utils->oldpwd.

1. Loops through the environment variables array utils->envp to find 
	the entry starting with "OLDPWD=".
2. If found, sets utils->oldpwd to point to this entry and returns 0 (success).
3. If not found, writes "PWD not found\n" to standard error and exits 
	the program with an error status.
*/
int	get_oldpwd(t_general *utils)
{
	int	i;

	i = 0;
	while (utils->envp[i] != NULL)
	{
		if (ft_strncmp(utils->envp[i], "OLDPWD=", 7) == 0)
		{
			utils->oldpwd = utils->envp[i];
			return (0);
		}
		i++;
	}
	if (utils->envp[i] == NULL)
	{
		ft_putstr_fd("PWD not found\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	return (ERROR);
}

/*
@brief : Calculates the number of strings in a null-terminated 
		array of strings.

*/
int	get_array_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

/*
@brief : Retrieves the value of the PATH environment variable

1. Loops through utils->envp to find the entry starting 
	with "PATH=".
2. If found, returns a dynamically allocated copy of the 
	PATH value (everything after "PATH=").
3. If not found, returns NULL.
*/
char	*get_path(t_general *utils)
{
	int	i;

	i = 0;
	while (utils->envp[i])
	{
		if (strncmp(utils->envp[i], "PATH=", 5) == 0)
			return (strdup(utils->envp[i] + 5));
		i++;
	}
	return (NULL);
}

/*
@brief : Parses the PATH environment variable and stores 
	the individual directories in utils->path.
1. Retrieves the full PATH string using get_path.
2. Splits the string into individual directories using 
	ft_split with : as the delimiter.
3. Frees the original longpath string as it is no longer needed.
4. Allocates memory for utils->path using ft_calloc, 
	ensuring it can hold all the directories plus a NULL terminator.
5. Calls join_path to process and store the directories in utils->path.
6. Frees the intermediate path array after transferring the data.
*/
void	store_path(t_general *utils)
{
	char	*longpath;
	char	**path;
	int		i;

	longpath = get_path(utils);
	path = ft_split(longpath, ':');
	free(longpath);
	i = get_array_size(path);
	utils->path = ft_calloc(i + 1, sizeof(char *));
	join_path(utils, path);
	free(path);
}
