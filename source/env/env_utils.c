/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:15:26 by nchok             #+#    #+#             */
/*   Updated: 2024/11/26 17:15:26 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

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
		if (path[i][ft_strlen(path[i]) - 1] != '/')
			path[i] = ft_strjoin(path[i], "/");
		if (ft_strncmp(path[i], "PATH=", 5) == 0)
			path[i] = ft_strtrim(path[i], "PATH=");
		utils->path[i] = path[i];
		i++;
	}
	free(path);
}
