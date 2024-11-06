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

int	pipes_errors(t_general *utils, t_type token_type)
{
	if (token_type == PIPE)
	{
		double_token_error(utils, utils->lexer_list, token_type);
		return (ERROR);
	}
	if (!utils->lexer_list)
	{
		parsing_error(1, utils, utils->lexer_list);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

t_parser	init_parser(t_general *utils, t_lexer *lexer_list)
{
	t_parser	parser;

	parser.lexer_list = lexer_list;
	parser.redirections = NULL;
	parser.redirections_count = 0;
	parser.utils = utils;
	return (parser);
}

int	start_parsing(t_general *utils)
{
	t_cmds			*cmds;
	t_parser		parser;

	utils->cmds = NULL;
	count_pipes(utils);
	if (utils->lexer_list->token_type == PIPE) // check if first token is pipe, throw error
		return (double_token_error(utils, utils->lexer_list, utils->lexer_list->token_type));
	while (utils->lexer_list)
	{
		if (utils->lexer_list && utils->lexer_list->token_type) // remove pipe from lexer
			del_one_node(&utils->lexer_list, utils->lexer_list->i);
		if (pipes_errors(utils, utils->lexer_list->token_type)) // check for pipe errors
			return (EXIT_FAILURE);
		parser = init_parser(utils, utils->lexer_list);
		cmds = init_cmds(&parser);
		if (!cmds)
			parsing_error(1, utils, utils->lexer_list);
		if (!utils->cmds)
			utils->cmds = cmds;
		else
			add_to_backcmds(&cmds, utils->cmds);
		utils->lexer_list = parser.lexer_list;
	}
	return (EXIT_SUCCESS);
}
