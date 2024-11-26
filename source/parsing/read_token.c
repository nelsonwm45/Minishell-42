/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 02:16:40 by nchok             #+#    #+#             */
/*   Updated: 2024/10/28 16:24:51 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../header/minishell.h"

/*
	@brief
	- check if the character is a space or tab

	@return
	- TRUE if it is a space or tab
	- FALSE if it is not a space or tab
*/
int	is_spaces(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (TRUE);
	return (FALSE);
}
/*
	@brief
	- remove space and tab from the line

	@param
	- line: the line to be checked
	- i: the index of the line

	@return
	- 0
*/
int	remove_space(char *line, int *i)
{
	int	j;
	
	j = *i;
	while (is_spaces(line[j]) == TRUE)
		j++;
	*i = j;
	return (0);
}

/*
	@brief
	- check if the character is a token (>, <, |)

	@param
	- c: the character to be checked

	@return
	- TRUE if it is a token
	- FALSE if it is not a token
*/
int	is_token(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (TRUE);
	return (FALSE);
}

/*
	@brief
	- get the token type

	@param
	- c: the character to be checked

	@return
	- return the token type in str form
*/
t_type	get_token_type(int c)
{
	if (c == '>')
		return (BIG);
	if (c == '<')
		return (SMALL);
	if (c == '|')
		return (PIPE);
	return (0);
}
/*
	@brief
	- check if current str has opening quotes,
	- if yes, find the closing quotes,

	@return
	- skip the quotes and return the next index
*/
int	handle_quotes(int i, char *str, char quote)
{
	int	j;

	j = 0;
	while (str[i + j] == quote)
	{
		j++;
		while (str[i + j] != quote && str[i + j])
			j++;
		j++;
	}
	return (j);
}

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
	
	token = get_token_type(str[i]); // get token type in str-num format
	if (token == BIG && str[i + 1] == '>') // check if double token
	{
		if (add_node_to_lexer(ft_strdup(">>"), BIGBIG, lexer_list) == 0)
			return (ERROR);
		return (2);
	}
	else if (token == SMALL && str[i + 1] == '<') // check if double token
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
	still need to fix
*/
int	handle_word(char *str, int i, t_lexer **lexer_list)
{	
	int	j;

	j = 0;
	while (str[i + j] && is_token(str[i + j]) == FALSE)
	{
		j += handle_quotes(i + j, str,'\"');
		j += handle_quotes(i + j, str,'\'');
		if (is_spaces(str[i + j]) == TRUE) // if space found, break
			break ;
		else 
			j++;
	}
	if (add_node_to_lexer(ft_substr(str, i, j), 0, lexer_list) == 0)
		return (ERROR);
	return (j);
}

int	read_token(t_general *utils)
{
	int		i;
	int		j;

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
