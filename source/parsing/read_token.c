/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:48:16 by nchok             #+#    #+#             */
/*   Updated: 2024/11/26 16:48:16 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/*
	@brief
	- check the token type and pass it to lexer

	@return
	- return 1 if single token
	- return 2 if double token
	- return 0 if not token

	@todo
	neeed to handle lexer
*/
int	handle_token(char *str, int i, t_lexer **lexer_list)
{
	t_type	token;

	token = get_token_type(str[i]);
	if (token == BIG && str[i + 1] == '>')
	{
		if (add_node_to_lexer(ft_strdup(">>"), BIGBIG, lexer_list) == 0)
			return (ERROR);
		return (2);
	}
	else if (token == SMALL && str[i + 1] == '<')
	{
		if (add_node_to_lexer(ft_strdup("<<"), SMALLSMALL, lexer_list) == 0)
			return (ERROR);
		return (2);
	}
	else if (token)
	{
		if (add_node_to_lexer(ft_substr(str, i, 1), token, lexer_list) == 0)
			return (ERROR);
		return (1);
	}
	return (0);
}

int	add_node_to_lexer(char *str, t_type token_type, t_lexer **lexer_list)
{
	t_lexer	*node;

	node = create_node(str, token_type);
	if (!node)
		return (0);
	add_to_backlexer(node, lexer_list);
	return (1);
}

/*
	@brief
	- handle the word in the line
*/
int	handle_word(char *str, int i, t_lexer **lexer_list)
{
	int	j;

	j = 0;
	while (str[i + j] && is_token(str[i + j]) == FALSE)
	{
		j += handle_quotes(i + j, str, '\"');
		j += handle_quotes(i + j, str, '\'');
		if (is_spaces(str[i + j]) == TRUE)
			break ;
		else
			j++;
	}
	if (add_node_to_lexer(ft_substr(str, i, j), 0, lexer_list) == 0)
		return (ERROR);
	return (j);
}

/*
	@brief
	- read the token from the line
	- pass the token to the lexer
*/
int	read_token(t_general *utils)
{
	int	i;
	int	j;

	i = 0;
	while (utils->line[i])
	{
		j = 0;
		remove_space(utils->line, &i);
		if (is_token(utils->line[i]) == TRUE)
			j = handle_token(utils->line, i, &utils->lexer_list);
		else
			j = handle_word(utils->line, i, &utils->lexer_list);
		if (j < 0)
			return (0);
		i += j;
	}
	return (1);
}
