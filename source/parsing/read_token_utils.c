/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_token_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:14:41 by nchok             #+#    #+#             */
/*   Updated: 2024/11/26 16:17:33 by nchok            ###   ########.fr       */
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
