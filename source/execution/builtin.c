/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:16:38 by hheng             #+#    #+#             */
/*   Updated: 2024/11/26 17:09:15 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Nelson

	@brief
	connecting parser to builtin functions
*/
int	prep_builtin(t_general *utils, t_cmds *cmds, t_shell *mini)
{
	if (utils->cmds->builtin == CD)
		return (ft_cd(cmds->str, mini->env_vars));
	else if (utils->cmds->builtin == ECHO)
		return (ft_echo(cmds->str));
	else if (cmds->builtin == ENV)
		return (ft_env(mini->env_vars));
	else if (cmds->builtin == EXIT)
	{
		ft_exit(mini, cmds->str);
		return (0);
	}
	else if (cmds->builtin == PWD)
		return (ft_pwd());
	else if (cmds->builtin == EXPORT)
		return (ft_export(cmds->str, mini->env_vars, mini->hidden_env_vars));
	else if (cmds->builtin == UNSET)
		return (ft_unset(cmds->str, mini));
	return (-1);
}
