/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:45:12 by nchok             #+#    #+#             */
/*   Updated: 2024/11/11 18:49:10 by nchok            ###   ########.fr       */
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

	// Check if the first token is a pipe and throw an error
	if (utils->lexer_list->token_type == PIPE)
		return (double_token_error(utils, utils->lexer_list, utils->lexer_list->token_type));
	
	// Main parsing loop
	while (utils->lexer_list)
	{
		// If we encounter a PIPE token, this means we have reached the end of a command.
		// We need to prepare to start parsing the next command after the pipe.
		// Remove the PIPE token from the lexer list as it's not part of any command
		
		if (utils->lexer_list->token_type == PIPE)
			del_one_node(&utils->lexer_list, utils->lexer_list->i);

		// Check for pipe-related syntax errors before proceeding
		if (pipes_errors(utils, utils->lexer_list->token_type))
			return (EXIT_FAILURE);

		// Initialize the parser with the current lexer list position
		// This sets up the parsing context for the current command
		parser = init_parser(utils, utils->lexer_list);

		// Parse the current command and get a new t_cmds node
		cmds = init_cmds(&parser);
		if (!cmds)
			parsing_error(1, utils, utils->lexer_list);

		// Add the new command node to the command list (utils->cmds)
		if (!utils->cmds)
			utils->cmds = cmds; // Set the head of the list if it's empty
		else
			add_to_backcmds(&utils->cmds, cmds); // Append to the end of the list otherwise
		// Move the lexer list pointer to the remaining unparsed tokens
		// This allows us to start parsing the next command (if any) in the next iteration
		utils->lexer_list = parser.lexer_list;
	}
	return (EXIT_SUCCESS);
}
