/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:34:47 by nchok             #+#    #+#             */
/*   Updated: 2024/11/19 17:08:06 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../header/minishell.h"

int	check_redir(t_cmds *cmds)
{
	t_lexer	*ptr;

	ptr = cmds->redir;
	while (cmds->redir)
	{
		if (cmds->redir->token_type == SMALL)
		{
			if (handle_infile(cmds->redir->str))
				return (EXIT_FAILURE);
		}
		else if (cmds->redir->token_type == BIG || cmds->redir->token_type == BIGBIG)
		{
			if (handle_outfile(cmds->redir))
				return (EXIT_FAILURE);
		}
		else if (cmds->redir->token_type == SMALLSMALL)
		{
			if (handle_infile(cmds->hd_file_name))
				return (EXIT_FAILURE);
		}
		cmds->redir = cmds->redir->next;
	}
	cmds->redir = ptr;
	return (EXIT_SUCCESS);
}

int	handle_infile(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: infile", STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (fd > 0 && dup2(fd, STDIN_FILENO) < 0)
	{
		ft_putstr_fd("\033[31m42Minishell-1.0: \033[0m", STDERR_FILENO);
		ft_putstr_fd("pipe error\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (fd > 0)
		close(fd);
	return (EXIT_SUCCESS);
}

int	handle_outfile(t_lexer *redir)
{
	int	fd;

	fd = append_or_trunc(redir);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: outfile: error\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (fd > 0 && dup2(fd, STDOUT_FILENO) < 0)
	{
		ft_putstr_fd("minishell: pipe error\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (fd > 0)
		close(fd);
	return (EXIT_SUCCESS);
}

int	append_or_trunc(t_lexer *redir)
{
	int	fd;

	if (redir->token_type == BIGBIG)
		fd = open(redir->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(redir->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (fd);
}
	