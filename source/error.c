/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:54:36 by nchok             #+#    #+#             */
/*   Updated: 2024/10/28 15:42:37 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../header/minishell.h"

int	double_token_error(t_lexer *lexer, t_type token_type)
{
	ft_putstr_fd("Syntax error near unexpected token ", STDERR_FILENO);
	if (token_type == PIPE)
		ft_putstr_fd("'|'\n", STDERR_FILENO);
	else if (token_type == BIG)
		ft_putstr_fd("'>'\n", STDERR_FILENO);
	else if (token_type == BIGBIG)
		ft_putstr_fd("'>>'\n", STDERR_FILENO);
	else if (token_type == SMALL)
		ft_putstr_fd("'<'\n", STDERR_FILENO);
	else if (token_type == SMALLSMALL)
		ft_putstr_fd("'<'\n", STDERR_FILENO);
	if (lexer)
		clean_lexer(&lexer);
	// clean_utils(utils);
	return (EXIT_FAILURE);
}

void	parsing_error(int error, t_general *utils, t_lexer *lexer)
{
	if (lexer)
		clean_lexer(&lexer);
	error_message(error, utils);
}

int	error_message(int error_code, t_general *utils)
{
	if (error_code == 0)
		ft_putstr_fd("Memory allocation failed\n", STDERR_FILENO);
	else if (error_code == 1)
		ft_putstr_fd("Syntax error near unexpected token 'newline'\n", STDERR_FILENO);
	else if (error_code == 2)
		ft_putstr_fd("Syntax error: unable to locate closing quote\n", STDERR_FILENO);
	else if (error_code == 3)
		ft_putstr_fd("Parser Error\n", STDERR_FILENO);
	else if (error_code == 4)
		ft_putstr_fd("Failed to Create Pipe\n", STDERR_FILENO);
	else if (error_code == 5)
		ft_putstr_fd("Failed to Create Fork\n", STDERR_FILENO);
	// if (utils->lexer_list)
	// 	clean_lexer(&utils->lexer_list);
	if (utils)
		clean_utils(utils);
	return (EXIT_FAILURE);
}

int	cmd_not_found(char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	return (UNKNOWN_COMMAND);
}
