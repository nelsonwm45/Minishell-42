/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:30:57 by nchok             #+#    #+#             */
/*   Updated: 2024/11/19 17:25:44 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../header/minishell.h"

int	start_heredoc(t_general *utils, t_cmds *cmds)
{
	t_lexer		*ptr;
	int		status;

	ptr = cmds->redir;
	status = EXIT_SUCCESS;
	while (ptr)
	{
		if (ptr->token_type == SMALLSMALL)
		{
			if (cmds->hd_file_name)
				free(cmds->hd_file_name);
			cmds->hd_file_name = create_hd_filename();
			status = mini_heredoc(utils, ptr, cmds->hd_file_name);
			if (status != EXIT_SUCCESS)
			{
				utils->exit_status = 1;
				return (clean_utils(utils));
			}
			
		}
		ptr = ptr->next;
	}
	ptr = cmds->redir; // probably not needed
	return (EXIT_SUCCESS);
}

/*
	@brief
	- create a filename for heredoc
	- filename will be in the format of /tmp/.minishell_hd_{index}
	- index will be incremented each time this function is called
*/
char	*create_hd_filename(void)
{
	static int	i = 0;
	char	*filename;
	char	*file_index;

	file_index = ft_itoa(i);
	if (!file_index)
		return (NULL);
	i++;
	filename = ft_strjoin("/tmp/.minishell_hd_", file_index);
	free(file_index);
	return (filename);
}

/*
	@brief
	- check if the string has quotes
		-if yes, flag it
		- remove quotes from the string
	- call create_heredoc
	- fork a child process
	- wait for the child process to finish
*/
int	mini_heredoc(t_general *utils, t_lexer *ptr, char *filename)
{
	int		status;
	int		have_quote;
	pid_t	pid;

	(void)filename;
	status = EXIT_SUCCESS;
	if ((ptr->str[0] == '\'' && ptr->str[ft_strlen(ptr->str) - 1] == '\'') || (ptr->str[0] == '\"' && ptr->str[ft_strlen(ptr->str) - 1] == '\"'))
		have_quote = 1;
	else
		have_quote = 0;
	remove_quotes(ptr->str, '\'');
	remove_quotes(ptr->str, '\"');
	utils->stop_heredoc = 0;
	utils->in_heredoc = 1;
	pid = fork();
	if (pid == 0)
		status = create_heredoc(utils, ptr, filename, have_quote);
	// signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	utils->in_heredoc = 0;
	utils->heredoc = 1;
	return (status);
}

/*
	@brief
	- create a heredoc file
	- read the input from the user
	- write the input to the file
	- close the file
*/
int	create_heredoc(t_general *utils, t_lexer *ptr, char *filename, int have_quote)
{
	int	pipe_fd[2];
	char	*line;

	(void)filename;
	if (pipe(pipe_fd) == -1)
		return (error_message(4, utils));
	// signal(SIGINT, SIG_DFL);
	line = readline("\033[0;32mHeredoc> \033[0m");
	while (line && ft_strncmp(ptr->str, line, ft_strlen(ptr->str)) == 0 && utils->stop_heredoc != 1)
	{
		if (have_quote == 1)
			line = expand_str(utils, line);
		ft_putendl_fd(line, pipe_fd[1]);
		free(line);
		line = readline("\033[0;32mHeredoc> \033[0m");
	}
	free(line);
	if (utils->stop_heredoc == 1 || !line)
		return (EXIT_FAILURE);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	return (EXIT_SUCCESS);
}
