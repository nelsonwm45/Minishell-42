/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:45:00 by hheng             #+#    #+#             */
/*   Updated: 2024/10/30 13:45:00 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_exit(t_shell *mini, char **cmd)
{
	// mini->exit_code= 1;
	// ft_putstr_fd("exit ", 2);
	// cmd[1] ? ft_putendl_fd("BYE ~ ❤", 2) : ft_putendl_fd("💚", 2);
	// if (cmd[1] && cmd[2])
	// {
	// 	mini->return_code = 1;
	// 	ft_putendl_fd("minishell: exit: too many arguments", 2);
	// }
	// else if (cmd[1] && ft_strisnum(cmd[1]) == 0)
	// {
	// 	mini->return_code = 255;
	// 	ft_putstr_fd("minishell: exit: ", 2);
	// 	ft_putstr_fd(cmd[1], 2);
	// 	ft_putendl_fd(": numeric argument required", 2);
	// }
	// else if (cmd[1])
	// 	mini->return_code = ft_atoi(cmd[1]);
	// else
	// 	mini->return_code = 0;

	printf("Exiting minishell...\n");
    free_tab(cmd);
    exit(mini->return_code);
}