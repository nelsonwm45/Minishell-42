/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_setup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:11:04 by nchok             #+#    #+#             */
/*   Updated: 2024/11/30 17:02:01 by hheng            ###   ########.fr       */
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
		utils->pid = ft_calloc(utils->pipecount + 1, sizeof(pid_t));
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

	if (!cmds)
	{
		return ;
	}
	utils->cmds = call_expander(utils, utils->cmds);
	if (cmds->builtin == EXIT || cmds->builtin == CD || cmds->builtin == EXPORT
		|| cmds->builtin == UNSET)
	{
		g_ret_number = prep_builtin(utils, cmds, utils->mini);
		return ;
	}
	start_heredoc(utils, cmds);
	pid = fork();
	if (pid < 0)
		error_message(5, utils);
	if (pid == 0)
		handle_cmd(utils, cmds);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_ret_number = WEXITSTATUS(status);
}

int	exec_complex_cmd(t_general *utils)
{
	int	pipe_fd[2];
	int	fd_in;

	fd_in = STDIN_FILENO;
	while (utils->cmds)
	{
		utils->cmds = call_expander(utils, utils->cmds);
		if (utils->cmds->next)
			pipe(pipe_fd);
		start_heredoc(utils, utils->cmds);
		ft_fork(utils, pipe_fd, utils->cmds, fd_in);
		close(pipe_fd[1]);
		if (utils->cmds->prev)
			close(fd_in);
		fd_in = check_fd_heredoc(utils, utils->cmds, pipe_fd);
		if (utils->cmds->next)
			utils->cmds = utils->cmds->next;
		else
			break ;
	}
	wait_pipe(utils, utils->pid, utils->pipecount);
	utils->cmds = travel_first_cmds(utils->cmds);
	return (0);
}
