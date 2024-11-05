/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:49:21 by nchok             #+#    #+#             */
/*   Updated: 2024/10/28 15:42:15 by hheng             ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	duplicate_env(char **envp, t_general *utils)
{
	int	size;
	int	i;
	char	**arr;
	
	size = 0;
	while (envp[size] != NULL)
		size++;
	arr = ft_calloc(size + 1, sizeof(char *));
	if (!arr)
		return (ERROR);
	i = 0;
	while (envp[i] != NULL)
	{
		arr[i] = ft_strdup(envp[i]);
		i++;
	}
	utils->envp = arr;
	return (0);
}

int	print_envp(t_general *utils)
{
	int	i;

	i = 0;
	while (utils->envp[i])
	{
		ft_putstr_fd(utils->envp[i], 1);
		write(1, "\n", 1);
		i++;
	}
	return (0);
}

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

int	get_array_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

/*
	@brief
	- get path from envp
	@return
	- return path
	@error handling
	- path not found
*/
char	*get_path(t_general *utils)
{
	int	i;

	i = 0;
	while (utils->envp[i] != NULL)
	{
		if (ft_strncmp(utils->envp[i], "PATH=", 5) == 0)
			return (utils->envp[i]);
		i++;
	}
	return (NULL);
}

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
	i = 0;
	while (path[i])
	{
		if (path[i][ft_strlen(path[i]) - 1] != '/') // check if last char is not '/'
			path[i] = ft_strjoin(path[i], "/");
		if (ft_strncmp(path[i], "PATH=", 5) == 0) // remove "PATH=" from path
			path[i] = ft_strtrim(path[i], "PATH=");
		utils->path[i] = path[i];
		i++;
	}
}

int	init_utils(t_general *utils)
{
	utils->line = NULL;
	utils->lexer_list = NULL;
	utils->cmds_list = NULL;
	return (0);
}

int	process_envp(char **envp, t_general *utils)
{
	// int i;

	duplicate_env(envp, utils);
	get_pwd(utils);
	get_oldpwd(utils);
	store_path(utils);
	init_signal(utils);
	init_utils(utils);
	return (0);
}