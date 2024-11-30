/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 02:20:36 by nchok             #+#    #+#             */
/*   Updated: 2024/11/29 05:31:30 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	process_heredoc_input(t_general *utils, t_lexer *ptr, int fd,
									int have_quote)
{
	char	*line;
	char	*processed_line;

	line = readline("\033[0;32mHeredoc> \033[0m");
	while (line && same_str(ptr->str, line) == 0 && utils->stop_heredoc != 1)
	{
		if (have_quote == 0)
		{
			processed_line = check_if_var(utils, line);
			ft_putendl_fd(processed_line, fd);
			free(processed_line);
		}
		else
		{
			ft_putendl_fd(line, fd);
		}
		free(line);
		line = readline("\033[0;32mHeredoc> \033[0m");
	}
	free(line);
}

char	*check_if_var(t_general *utils, char *line)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	tmp = ft_strdup("\0");
	while (line[i])
	{
		j = i;
		if (line[i] == '$' && line[i + 1] != ' ' && line[i + 1] != '\0')
		{
			j += subs_dollar_var(utils, line, &tmp, i);
			i = j;
		}
		else
			i = append_str(&tmp, line[i], i);
	}
	line = tmp;
	return (line);
}

static int	handle_heredoc_child(t_general *utils, t_lexer *ptr,
	char *filename, int have_quote)
{
	int		fd;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	process_heredoc_input(utils, ptr, fd, have_quote);
	close(fd);
	if (utils->stop_heredoc == 1)
	{
		unlink(filename);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

int	create_heredoc(t_general *utils, t_lexer *ptr, char *filename,
	int have_quote)
{
	int		pid;

	pid = fork();
	if (pid == 0)
		handle_heredoc_child(utils, ptr, filename, have_quote);
	else if (pid > 0)
	{
		if (check_child_interrupt(pid) != EXIT_SUCCESS)
		{
			utils->stop_heredoc = 1;
			unlink(filename);
			write(STDERR_FILENO, "signal SIGINT interrupt\n", 24);
			return (EXIT_FAILURE);
		}
	}
	else
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
