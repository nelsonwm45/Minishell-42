/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:45:00 by hheng             #+#    #+#             */
/*   Updated: 2024/11/29 04:23:36 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Check for
	- No arguments.
	- Valid numeric arguments (e.g., exit 42).
	-Invalid arguments (e.g., exit abc). 
	- shd return 2, but it return 255 --> need to double check and fix
*/

static void	print_exit_message(char **cmd)
{
	ft_putstr_fd("exit ", 2);
	if (cmd[1])
		ft_putendl_fd("BYE ~ ❤", 2);
	else
		ft_putendl_fd("💚", 2);
}

void	ft_exit(t_shell *mini, char **cmd)
{
	mini->exit_code = 1;
	print_exit_message(cmd);
	if (cmd[1] && !ft_strisnum(cmd[1]))
	{
		mini->return_code = 2;
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit(mini->return_code);
	}
	if (cmd[1] && cmd[2])
	{
		mini->return_code = 1;
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		exit(mini->return_code);
	}
	if (!cmd[1])
	{
		mini->exit_code = 0;
		mini->return_code = 0;
		exit(mini->return_code);
	}
	mini->return_code = ft_atoi(cmd[1]) % 256;
	exit(mini->return_code);
}
