/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 02:11:34 by nchok             #+#    #+#             */
/*   Updated: 2024/11/27 15:57:52 by nchok            ###   ########.fr       */
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
				g_ret_number = 1;
				return (clean_utils(utils));
			}
		}
		ptr = ptr->next;
	}
	return (EXIT_SUCCESS);
}

char	*create_hd_filename(t_general *utils)
{
	static int	i = 0;
	char		*filename;
	char		*file_index;
	char		*pwd;
	char		*tmp;

	file_index = ft_itoa(i++);
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

int	mini_heredoc(t_general *utils, t_lexer *ptr, char *filename)
{
	int	status;
	int	have_quote;

	g_ret_number = -42;
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
	utils->in_heredoc = 0;
	utils->heredoc = 1;
	return (status);
}

int	check_child_interrupt(int pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (EXIT_FAILURE);
	if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
