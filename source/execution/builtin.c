/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:16:38 by hheng             #+#    #+#             */
/*   Updated: 2024/11/19 16:59:59 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_builtin(char *command)
{
	if (ft_strcmp(command, "echo") == 0)
		return (1);
	if (ft_strcmp(command, "cd") == 0)
		return (1);
	if (ft_strcmp(command, "pwd") == 0)
		return (1);
	if (ft_strcmp(command, "env") == 0)
		return (1);
	if (ft_strcmp(command, "export") == 0)
		return (1);
	if (ft_strcmp(command, "unset") == 0)
		return (1);
	if (ft_strcmp(command, "exit") == 0)
		return (1);
	return (0);
}

int exec_builtin(char **args, t_shell *mini)
{
    // printf("exec_builtin called with command: %s\n", args[0]);

    if (ft_strcmp(args[0], "cd") == 0)
        return ft_cd(args, mini->env_vars);
    else if (ft_strcmp(args[0], "echo") == 0)
        return ft_echo(args);
    else if (ft_strcmp(args[0], "env") == 0)
        return ft_env(mini->env_vars);
	  else if (ft_strcmp(args[0], "exit") == 0)
    {
        ft_exit(mini, args);
        return 0; 
    }
    else if (ft_strcmp(args[0], "export") == 0)
    {
        printf("Calling ft_export\n");
        printf("env: %p, secret: %p\n", (void *)mini->env_vars, (void *)mini->hidden_env_vars);
        return ft_export(args, mini->env_vars, mini->hidden_env_vars);
    }
    else if (ft_strcmp(args[0], "pwd") == 0)
        return ft_pwd();
    else if (ft_strcmp(args[0], "unset") == 0)
        return ft_unset(args, mini);
    return -1; // Command not found
}

/*
	Nelson

	@brief
	connecting parser to builtin functions
*/
int prep_builtin(t_general *utils, t_cmds *cmds, t_shell *mini)
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
		return(ft_export(cmds->str, mini->env_vars, mini->hidden_env_vars));
	else if (cmds->builtin == UNSET)
		return (ft_unset(cmds->str, mini));
	return (-1);
}
