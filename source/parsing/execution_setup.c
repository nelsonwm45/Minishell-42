/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_setup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:11:04 by nchok             #+#    #+#             */
/*   Updated: 2024/11/14 12:23:47 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	setup_executor(t_general *utils)
{
	signal(SIGQUIT, sig_quit);
	utils->in_cmd = 1;
	if (utils->pipecount == 0)
		exec_simple_cmd(utils, utils->cmds);
	else
	{
		utils->pid = ft_calloc(utils->pipecount, sizeof(pid_t));
		if (!utils->pid)
			return (error_message(0, utils));
		exec_complex_cmd(utils);
	}
	utils->in_cmd = 0;
	return (EXIT_SUCCESS);
}

void	exec_simple_cmd(t_general *utils, t_cmds *cmds)
{
	utils->cmds = call_expander(utils, utils->cmds);
	if (cmds->builtin == CD || cmds->builtin == PWD || cmds->builtin == EXPORT || cmds->builtin == UNSET)
	{
		utils->exit_status = exec_builtin(cmds->str, (t_shell *)utils);
		return ;
	}
	check_heredoc(utils, cmds);
}

int	exec_complex_cmd(t_general *utils)
{
	
	
}