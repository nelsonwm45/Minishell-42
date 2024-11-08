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

// char	**duplicate_env(char **envp)
// {
// 	int	size;
// 	int	i;
// 	char	**arr;
	
// 	size = 0;
// 	while (envp[size] != NULL)
// 		size++;
// 	arr = ft_calloc(size + 1, sizeof(char *));
// 	if (!arr)
// 		return (NULL);
// 	i = 0;
// 	while (envp[i] != NULL)
// 	{
// 		arr[i] = ft_strdup(envp[i]);
// 		if (arr[i] == NULL)
// 		{
// 			free_array(arr);
// 			return (arr);
// 		}
// 		i++;
// 	}
// 	return (arr);
// }

// int	print_envp(t_general *utils)
// {
// 	int	i;

// 	i = 0;
// 	while (utils->envp[i])
// 	{
// 		ft_putstr_fd(utils->envp[i], 1);
// 		write(1, "\n", 1);
// 		i++;
// 	}
// 	return (0);
// }

// int	get_pwd(t_general *utils)
// {
// 	int	i;
	
// 	i = 0;
// 	while (utils->envp[i] != NULL)
// 	{
// 		if (ft_strncmp(utils->envp[i], "PWD=", 4) == 0)
// 		{
// 			utils->pwd = utils->envp[i];
// 			return (0);
// 		}
// 		i++;
// 	}
// 	if (utils->envp[i] == NULL)
// 	{
// 		ft_putstr_fd("PWD not found\n", STDERR_FILENO);
// 		exit(EXIT_FAILURE);
// 	}
// 	return (ERROR);
// }

// int	get_oldpwd(t_general *utils)
// {
// 		int	i;
	
// 	i = 0;
// 	while (utils->envp[i] != NULL)
// 	{
// 		if (ft_strncmp(utils->envp[i], "OLDPWD=", 7) == 0)
// 		{
// 			utils->oldpwd = utils->envp[i];
// 			return (0);
// 		}
// 		i++;
// 	}
// 	if (utils->envp[i] == NULL)
// 	{
// 		ft_putstr_fd("PWD not found\n", STDERR_FILENO);
// 		exit(EXIT_FAILURE);
// 	}
// 	return (ERROR);
// }

// int	get_array_size(char **arr)
// {
// 	int	i;

// 	i = 0;
// 	while (arr[i] != NULL)
// 		i++;
// 	return (i);
// }

// char *get_env_value(char *var_name, t_env *env)
// {
//     while (env)
//     {
//         if (ft_strncmp(env->value, var_name, ft_strlen(var_name)) == 0 && env->value[ft_strlen(var_name)] == '=')
//             return (env->value + ft_strlen(var_name) + 1);
//         env = env->next;
//     }
//     return NULL;
// }

// char *get_path(t_general *utils)
// {
//     int i = 0;

//     // Iterate through the environment variable array `envp`
//     while (utils->envp[i])
//     {
//         // Check if the current environment variable starts with "PATH="
//         if (strncmp(utils->envp[i], "PATH=", 5) == 0)
//         {
//             // Duplicate the path string (without "PATH=") and return it
//             return strdup(utils->envp[i] + 5);
//         }
//         i++;
//     }
//     return NULL; // Return NULL if "PATH=" is not found
// }

// void	store_path(t_general *utils)
// {
// 	char	*longpath;
// 	char	**path;
// 	int		i;

// 	longpath = get_path(utils);
// 	path = ft_split(longpath, ':');
// 	i = get_array_size(path);
// 	utils->path = ft_calloc(i + 1, sizeof(char *));
// 	i = 0;
// 	while (path[i])
// 	{
// 		if (path[i][ft_strlen(path[i]) - 1] != '/') // check if last char is not '/'
// 			path[i] = ft_strjoin(path[i], "/");
// 		if (ft_strncmp(path[i], "PATH=", 5) == 0) // remove "PATH=" from path
// 			path[i] = ft_strtrim(path[i], "PATH=");
// 		utils->path[i] = path[i];
// 		i++;
// 	}
// }

// int	init_utils(t_general *utils)
// {
// 	utils->line = NULL;
// 	utils->lexer_list = NULL;
// 	utils->cmds = NULL;
// 	return (0);
// }

// int	process_envp(char **envp, t_general *utils)
// {
// 	utils->envp = duplicate_env(envp);
// 	get_pwd(utils);
// 	get_oldpwd(utils);
// 	store_path(utils);
// 	// init_signal(utils);
// 	init_utils(utils);
// 	return (0);

