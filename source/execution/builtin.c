/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:16:38 by hheng             #+#    #+#             */
/*   Updated: 2024/11/18 11:24:02 by nchok            ###   ########.fr       */
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
int prep_builtin(t_general *utils, t_env *env, t_shell *mini)
{
	if (utils->cmds->builtin == CD)
		return (ft_cd(utils->cmds->str, mini->env_vars));
	else if (utils->cmds->builtin == ECHO)
		return (ft_echo(utils->cmds->str));
	else if (utils->cmds->builtin == ENV)
		return (ft_env(mini->env_vars));
	else if (utils->cmds->builtin == EXIT)
	{
		ft_exit(mini, utils->cmds->str);
		return (0);
	}
	else if (utils->cmds->builtin == PWD)
		return (ft_pwd());
	else if (utils->cmds->builtin == EXPORT)
		return(ft_export(utils->cmds->str, mini->env_vars, mini->hidden_env_vars));
	else if (utils->cmds->builtin == UNSET)
	{
		ft_unset(utils->cmds->str, mini);
		return (EXIT_SUCCESS);
	}
}
