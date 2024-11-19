/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_setup_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:11:16 by nchok             #+#    #+#             */
/*   Updated: 2024/11/19 15:03:23 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../header/minishell.h"

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