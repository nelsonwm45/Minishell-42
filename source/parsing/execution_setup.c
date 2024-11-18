/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_setup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:11:04 by nchok             #+#    #+#             */
/*   Updated: 2024/11/18 10:23:14 by nchok            ###   ########.fr       */
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
	int	pid;
	int	status;

	utils->cmds = call_expander(utils, utils->cmds);
	if (cmds->builtin == CD || cmds->builtin == PWD || cmds->builtin == EXPORT || cmds->builtin == UNSET)
	{
		utils->exit_status = exec_builtin(cmds->str, (t_shell *)utils);
		return ;
	}
	check_heredoc(utils, cmds);
	pid = fork();
	if (pid < 0)
		return (error_message(5, utils));
	if (pid == 0)
		handle_cmd(utils, cmds);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		utils->exit_status = WEXITSTATUS(status);
}

int	exec_complex_cmd(t_general *utils)
{
	
	
}