/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_setup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:11:04 by nchok             #+#    #+#             */
/*   Updated: 2024/11/19 15:57:45 by nchok            ###   ########.fr       */
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
	int	pipe_fd[2];
	int	fd_in;

	fd_in = STDIN_FILENO;
	while (utils->cmds)
	{
		utils->cmds = call_expander(utils, utils->cmds);
		if (utils->cmds->next)
			pipe(pipe_fd);
		start_heredoc(utils, utils->cmds);
		ft_fork(utils, pipe_fd, fd_in, utils->cmds);
		close(pipe_fd[1]);
		if (utils->cmds->prev)
			close(fd_in);
		fd_in = check_fd_heredoc(utils, utils->cmds, pipe_fd);
		if (utils->cmds->next)
			utils->cmds = utils->cmds->next;
		else
			break ;
	}
}

int	ft_fork(t_general *utils, int pipe_fd[2], int fd_in, t_cmds *cmds)
{
	static int	i = 0;

	if (utils->reset == 1)
	{
		utils->reset = 0;
		i = 0;
	}
	utils->pid[i] = fork();
	if (utils->pid[i] < 0)
		error_message(5, utils);
	if (utils->pid[i] == 0)
		dup2_cmd(cmds, utils, pipe_fd, fd_in);
	i++;
	return (EXIT_SUCCESS);
}
