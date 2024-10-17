/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 02:16:40 by nchok             #+#    #+#             */
/*   Updated: 2024/10/18 02:54:17 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../header/minishell.h"

int	remove_space(char *line, int *i)
{
	int	j;
	
	j = *i;
	while (line[j] == ' ' || line[j] == '\t')
		j++;
	*i = j;
	return (0);
}

int	is_token(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (TRUE);
	return (FALSE);
}

t_token	get_token_type(int c)
{
	static int token_list[3][2] = {
		{'>', GREAT},
		{'<', LESS},
		{'|', PIPE}
	};
	int	i;

	i = 0;
	while (i < 3)
	{
		if (c == token_list[i][0])
			return (token_list[i][1]); // return token type in str form
		i++;	
	}
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
int	handle_token(char *str, int i)
{
	t_token	token;
	
	token = get_token_type(str[i]); // get token type in str format
	if (token == GREAT && str[i + 1] == '>')
	{
		// handle double greater than
		printf("Double greater than\n");
		return (2);
	}
	else if (token == LESS && str[i + 1] == '<')
	{
		// handle double less than
		printf("Double less than\n");
		return (2);
	}
	else if (token)
	{
		// handle single token
		printf("Single token\n");
		return (1);
	}
	return (0);
}

int	read_token(t_env *utils)
{
	int		i;
	int		j;

	i = 0;
	while (utils->line[i])
	{
		j = 0;
		remove_space(utils->line[i], &i);
		if (is_token == TRUE)
			j = handle_token(utils->line[i], i);
		else
			j = handle_word(utils->line[i], i);
		if (j < 0)
			return (0);
		i += j;
	}
	return (1);
}