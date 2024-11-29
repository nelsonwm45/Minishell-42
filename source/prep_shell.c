/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:19:54 by nchok             #+#    #+#             */
/*   Updated: 2024/11/27 17:22:35 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	init_utils(t_general *utils)
{
	utils->line = NULL;
	utils->env_vars = NULL;
	utils->lexer_list = NULL;
	utils->cmds = NULL;
	utils->envp = NULL;
	utils->path = NULL;
	utils->pwd = NULL;
	utils->oldpwd = NULL;
	utils->pipecount = 0;
	utils->in_cmd = 0;
	utils->pid = 0;
	utils->reset = 0;
	utils->stop_heredoc = 0;
	utils->in_heredoc = 0;
	utils->heredoc = 0;
	return (0);
}

int	process_envp(char **envp, t_general *utils)
{
	init_utils(utils);
	if (utils->envp)
		free_array(utils->envp);
	utils->envp = duplicate_env(envp);
	get_pwd(utils);
	get_oldpwd(utils);
	store_path(utils);
	return (0);
}

char	**duplicate_env(char **envp)
{
	int		size;
	int		i;
	char	**arr;

	size = 0;
	while (envp[size] != NULL)
		size++;
	arr = ft_calloc(size + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		arr[i] = ft_strdup(envp[i]);
		if (!arr[i])
		{
			free_array(arr);
			return (NULL);
		}
		i++;
	}
	return (arr);
}
