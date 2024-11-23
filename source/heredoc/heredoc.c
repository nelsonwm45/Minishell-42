/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 02:11:34 by nchok             #+#    #+#             */
/*   Updated: 2024/11/23 16:31:29 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	start_heredoc(t_general *utils, t_cmds *cmds)
{
	t_lexer	*ptr;
	int		status;

	ptr = cmds->redir;
	status = EXIT_SUCCESS;
	while (ptr)
	{
		if (ptr->token_type == SMALLSMALL)
		{
			if (cmds->hd_file_name)
				free(cmds->hd_file_name);
			cmds->hd_file_name = create_hd_filename(utils);
			status = mini_heredoc(utils, ptr, cmds->hd_file_name);
			if (status != EXIT_SUCCESS)
			{
				utils->exit_status = 1;
				return (clean_utils(utils));
			}
		}
		ptr = ptr->next;
	}
	return (EXIT_SUCCESS);
}

/*
	@brief
	- create a filename for heredoc
	- filename will be in the format of /tmp/.minishell_hd_{index}
	- index will be incremented each time this function is called
*/
char	*create_hd_filename(t_general *utils)
{
	static int	i = 0;
	char		*filename;
	char		*file_index;
	char		*pwd;
	char		*tmp;

	file_index = ft_itoa(i);
	i++;
	pwd = utils->pwd;
	pwd = remove_pwd(pwd);
	tmp = ft_strjoin(pwd, "/.minishell_hd_");
	filename = ft_strjoin(tmp, file_index);
	free(tmp);
	free(file_index);
	return (filename);
}

char	*remove_pwd(char *pwd)
{
	int			i;
	int			j;
	const char	*str;

	i = 0;
	j = 0;
	str = "PWD=";
	while (pwd[i] && str[j])
	{
		if (pwd[i] == str[j])
		{
			i++;
			j++;
		}
	}
	return (pwd + j);
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
	int	status;
	int	have_quote;

	status = EXIT_SUCCESS;
	if ((ptr->str[0] == '\'' && ptr->str[ft_strlen(ptr->str) - 1] == '\'')
		|| (ptr->str[0] == '\"' && ptr->str[ft_strlen(ptr->str) - 1] == '\"'))
		have_quote = 1;
	else
		have_quote = 0;
	remove_quotes(ptr->str, '\'');
	remove_quotes(ptr->str, '\"');
	utils->stop_heredoc = 0;
	utils->in_heredoc = 1;
	create_heredoc(utils, ptr, filename, have_quote);
	// signal(SIGQUIT, SIG_IGN);
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
int	create_heredoc(t_general *utils, t_lexer *ptr, char *filename,
		int have_quote)
{
	int		fd;
	char	*line;

	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	line = readline("\033[0;32mHeredoc> \033[0m");
	while (line && ft_strncmp(ptr->str, line, ft_strlen(ptr->str)) != 0
		&& utils->stop_heredoc != 1)
	{
		if (have_quote == 0)
			line = expand_str(utils, line);
		ft_putendl_fd(line, fd);
		free(line);
		line = readline("\033[0;32mHeredoc> \033[0m");
	}
	free(line);
	if (utils->stop_heredoc == 1 || !line)
		return (EXIT_FAILURE);
	close(fd);
	return (EXIT_SUCCESS);
}
