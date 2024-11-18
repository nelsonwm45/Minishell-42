/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:26:00 by nchok             #+#    #+#             */
/*   Updated: 2024/11/18 13:44:25 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	handle_cmd(t_general *utils, t_cmds *cmds)
{
	int	exit_code;

	exit_code = 0;
	if (cmds->redir)
		if (check_redir(cmds))
			exit(1);
	if (cmds->builtin != NULL) // execute builtin here
	{
		exit_code = prep_builtin(utils, cmds, utils->mini);
		exit(exit_code);
	}
	else if (cmds->str[0][0] != '\0')
		exit_code = search_cmd(utils, cmds);
	exit(exit_code);
}

int	search_cmd(t_general *utils, t_cmds *cmds)
{
	int	i;
	char	*new_cmd;

	cmds->str = resplit_str(cmds->str);
	if (!access(cmds->str[0], F_OK))
		execve(cmds->str[0], cmds->str, utils->envp);
	while (utils->path[i])
	{
		new_cmd = ft_strjoin(utils->path[i], cmds->str[0]);
		if (!access(new_cmd, F_OK))
			execve(new_cmd, cmds->str, utils->envp);
		free(new_cmd);
		i++;
	}
	return (cmd_not_found(cmds->str[0]));
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
void	dup2_cmd(t_cmds *cmds, t_general *utils, int pipe_fd[2], int std_in)
{
	if (cmds->prev && dup2(std_in, STDIN_FILENO) < 0)
		error_message(4, utils);
	close(pipe_fd[0]);
	if (cmds->next && dup2(pipe_fd[1], STDOUT_FILENO) < 0)
		error_message(4, utils);
	close(pipe_fd[1]);
	if (cmds->prev)
		close(std_in);
	handle_cmd(utils, cmds);
}
