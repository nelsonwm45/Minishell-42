/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:51:28 by nchok             #+#    #+#             */
/*   Updated: 2024/11/26 16:42:33 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/*
	@brief
	- create a cmds node
	- might need to handle builtin for each node
*/
t_cmds	*create_cmds(char **str, t_lexer *redirections, int redir_count)
{
	t_cmds	*cmds;

	cmds = ft_calloc(1, sizeof(t_cmds));
	if (!cmds)
		return (0);
	cmds->str = str;
	cmds->redir_count = redir_count;
	cmds->hd_file_name = NULL;
	cmds->builtin = check_builtin(str[0]);
	cmds->redir = redirections;
	cmds->next = NULL;
	cmds->prev = NULL;
	return (cmds);
}

void	add_to_backcmds(t_cmds **parse_cmds, t_cmds *utils_cmds)
{
	t_cmds	*ptr;

	ptr = *parse_cmds;
	if (*parse_cmds == NULL)
	{
		*parse_cmds = utils_cmds;
		return ;
	}
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = utils_cmds;
	utils_cmds->prev = ptr;
}

t_builtin	check_builtin(char *str)
{
	if (same_str(str, "cd") == 1)
		return (CD);
	if (same_str(str, "echo") == 1)
		return (ECHO);
	if (same_str(str, "env") == 1)
		return (ENV);
	if (same_str(str, "export") == 1)
		return (EXPORT);
	if (same_str(str, "pwd") == 1)
		return (PWD);
	if (same_str(str, "unset") == 1)
		return (UNSET);
	if (same_str(str, "exit") == 1)
		return (EXIT);
	return (NOT_BUILTIN);
}
