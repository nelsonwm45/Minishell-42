/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:45:12 by nchok             #+#    #+#             */
/*   Updated: 2024/10/30 14:45:22 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../header/minishell.h"

/*
	count the number of pipes in the lexer list
*/
int	count_pipes(t_general *utils)
{
	t_lexer *ptr;

	ptr = utils->lexer_list;
	utils->pipecount = 0;
	while (ptr)
	{
		if (ptr->token_type == PIPE)
			utils->pipecount++;
		ptr = ptr->next;
	}
	return (0);
}

int	start_parsing(t_general *utils)
{
	t_simple_cmds	*node;
	t_parser		parser;

	utils->cmds = NULL;
	count_pipes(utils);
	if (utils->lexer_list->token_type == PIPE) // check if first token is pipe, throw error
		return (double_token_error(utils, utils->lexer_list, utils->lexer_list->token_type));
	while (utils->lexer_list)
	{
		if (utils->lexer_list && utils->lexer_list->token_type) // remove pipe from lexer
			del_one_node(&utils->lexer_list, utils->lexer_list->i);
		
		utils->lexer_list = utils->lexer_list->next;
	}
}