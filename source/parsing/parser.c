/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:45:12 by nchok             #+#    #+#             */
/*   Updated: 2024/11/26 12:34:13 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../header/minishell.h"

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
		double_token_error(utils->lexer_list, token_type);
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
	// t_cmds			*cmds;
	// t_parser		parser;
	t_type			token;

	utils->cmds = NULL;
	count_pipes(utils);
	token = scan_double_token(utils->lexer_list);
	if (token != 0)
		return (double_token_error(utils->lexer_list, token));
	if (process_parser(utils) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	// while (utils->lexer_list)
	// {
	// 	if (utils->lexer_list->token_type == PIPE)
	// 		del_one_node(&utils->lexer_list, utils->lexer_list->i);
	// 	if (pipes_errors(utils, utils->lexer_list->token_type))
	// 		return (EXIT_FAILURE);
	// 	parser = init_parser(utils, utils->lexer_list);
	// 	cmds = init_cmds(&parser);
	// 	print_lexer(cmds->redir);
	// 	if (!cmds)
	// 		parsing_error(1, utils, utils->lexer_list);
	// 	if (!utils->cmds)
	// 		utils->cmds = cmds; // Set the head of the list if it's empty
	// 	else
	// 		add_to_backcmds(&utils->cmds, cmds); // Append to the end of the list otherwise
	// 	utils->lexer_list = parser.lexer_list;
	// }
	return (EXIT_SUCCESS);
}

int	process_parser(t_general *utils)
{
	t_cmds	*cmds;
	t_parser	parser;

	while (utils->lexer_list)
	{
		if (utils->lexer_list->token_type == PIPE)
			del_one_node(&utils->lexer_list, utils->lexer_list->i);
		if (pipes_errors(utils, utils->lexer_list->token_type))
			return (EXIT_FAILURE);
		parser = init_parser(utils, utils->lexer_list);
		cmds = init_cmds(&parser);
		if (!cmds)
			parsing_error(1, utils, utils->lexer_list);
		if (!utils->cmds)
			utils->cmds = cmds; // Set the head of the list if it's empty
		else
			add_to_backcmds(&utils->cmds, cmds); // Append to the end of the list otherwise
		utils->lexer_list = parser.lexer_list;
	}
	return (EXIT_SUCCESS);
}

