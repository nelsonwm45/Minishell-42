/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:22:27 by nchok             #+#    #+#             */
/*   Updated: 2024/11/19 16:28:23 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

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


/*
	- manage the input/output redirection 
	and pipe handling for a shell-like command execution framework
	- uses the dup2 function to set up the file descriptors for commands in a pipeline.
	
	cmd1 | cmd2 | cmd3
	
	cmd 1
	- no previous command, no input redirection
	- cmd1's output is connected to cmd2's input

	cmd 2
	- cmd1's output is connected to cmd2's input
	- cmd2's output is connected to cmd3's input

	cmd 3
	- cmd2's output is connected to cmd3's input
	- no next command, no output redirection

*/
void	dup2_cmd(t_cmds *cmds, t_general *utils, int pipe_fd[2], int fd_in)
{
	if (cmds->prev && dup2(fd_in, STDIN_FILENO) < 0)
		error_message(4, utils);
	close(pipe_fd[0]);
	if (cmds->next && dup2(pipe_fd[1], STDOUT_FILENO) < 0)
		error_message(4, utils);
	close(pipe_fd[1]);
	if (cmds->prev)
		close(fd_in);
	handle_cmd(utils, cmds);
}

t_cmds	*travel_first_cmds(t_cmds *cmds)
{
	int	i;

	i = 0;
	if (!cmds)
		return (NULL);
	while (cmds->prev != NULL)
	{
		cmds = cmds->prev;
		i++;
	}
	return (cmds);
}

int	check_fd_heredoc(t_general *utils, t_cmds *cmds, int pipe_fd[2])
{
	int	fd_in;

	if (utils->heredoc) // if in heredoc
	{
		close(pipe_fd[0]); // close read end of pipe
		fd_in = open(cmds->hd_file_name, O_RDONLY); // open heredoc file
	}
	else
		fd_in = STDIN_FILENO; // set fd_in to stdin
	return (fd_in);
}

int	wait_pipe(t_general *utils, int *pid, int pipecount)
{
	int	i;
	int	status;

	i = 0;
	while (i < pipecount)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
		utils->exit_status = WEXITSTATUS(status);
	return (EXIT_SUCCESS);
}