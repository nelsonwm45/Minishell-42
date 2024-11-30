/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:26:00 by nchok             #+#    #+#             */
/*   Updated: 2024/11/30 15:14:40 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	handle_cmd(t_general *utils, t_cmds *cmds)
{
	int	exit_code;

	exit_code = 0;
	if (cmds->redir)
		if (check_redir(cmds))
			exit(1);
	if (!cmds->str || cmds->str[0] == NULL || cmds->str[0][0] == '\0')
	{
		exit(0);
	}
	if (cmds->builtin != 0)
	{
		exit_code = prep_builtin(utils, cmds, utils->mini);
		exit(exit_code);
	}
	else if (cmds->str[0][0] != '\0')
		exit_code = search_cmd(utils, cmds);
	exit(exit_code);
}

int	search_cmd(t_general *utils, t_cmds *cmds)
{
	int		i;
	char	*new_cmd;
	char	**envp;
	char	**path;

	path = NULL;
	envp = NULL;
	cmds->str = resplit_str(cmds->str);
	i = 0;
	envp = convert_envp_to_str(utils->mini->env_vars);
	path = find_path(utils->mini->env_vars);
	if (!access(cmds->str[0], F_OK))
		execve(cmds->str[0], cmds->str, envp);
	while (path != NULL && path[i])
	{
		new_cmd = ft_strjoin(path[i], cmds->str[0]);
		if (!access(new_cmd, F_OK))
			execve(new_cmd, cmds->str, envp);
		free(new_cmd);
		i++;
	}
	free_array(envp);
	free_array(path);
	return (cmd_not_found(cmds->str[0]));
}

char	**convert_envp_to_str(t_env *env)
{
	int		i;
	char	**envp;
	t_env	*ptr;

	i = 0;
	ptr = env;
	while (ptr)
	{
		i++;
		ptr = ptr->next;
	}
	envp = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	ptr = env;
	while (ptr)
	{
		envp[i] = ft_strdup(ptr->value);
		i++;
		ptr = ptr->next;
	}
	envp[i] = NULL;
	return (envp);
}
