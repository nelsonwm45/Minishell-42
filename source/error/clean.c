/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:10:40 by nchok             #+#    #+#             */
/*   Updated: 2024/12/06 11:03:25 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/*
	@brief
	- free the array
*/
void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	clean_utils(t_general *utils)
{
	if (utils->cmds)
		clean_cmd(&utils->cmds);
	free(utils->line);
	if (utils->pid)
		free(utils->pid);
	init_utils(utils);
	utils->reset = 1;
	return (0);
}

int	clean_lexer(t_lexer **lexer)
{
	t_lexer	*ptr;

	if (!lexer || !*lexer)
		return (0);
	while (*lexer)
	{
		ptr = (*lexer)->next;
		if ((*lexer)->str)
			free((*lexer)->str);
		free(*lexer);
		*lexer = ptr;
	}
	*lexer = NULL;
	return (0);
}

void	clean_cmd(t_cmds **cmds)
{
	t_cmds	*ptr;
	t_lexer	*redir;

	if (!cmds || !*cmds)
		return ;
	*cmds = travel_first_cmds(*cmds);
	while (*cmds)
	{
		ptr = (*cmds)->next;
		redir = (*cmds)->redir;
		clean_lexer(&redir);
		if ((*cmds)->str)
			free_array((*cmds)->str);
		if ((*cmds)->hd_file_name)
		{
			unlink((*cmds)->hd_file_name);
			free((*cmds)->hd_file_name);
		}
		free(*cmds);
		*cmds = ptr;
	}
	*cmds = NULL;
}
