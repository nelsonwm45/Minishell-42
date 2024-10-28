/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 02:16:40 by nchok             #+#    #+#             */
/*   Updated: 2024/10/28 12:36:45 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../header/minishell.h"

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
	while (line[j] == ' ' || line[j] == '\t')
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
	
	
*/
t_token	get_token_type(int c)
{
	static int token_list[3][2] = {
		{'>', BIG},
		{'<', SMALL},
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
	return (0);
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
	printf("Token: %d\n", token);
	if (token == BIG && str[i + 1] == BIG)
	{
		// handle double bigger than
		printf("Double bigger than\n");
		return (2);
	}
	else if (token == SMALL && str[i + 1] == SMALL)
	{
		// handle double small than
		printf("Double small than\n");
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
/*
	still need to fix
*/
int	handle_word(char *str, int i)
{	
	while (str[i] && str[i] != ' ' && str[i] != '\t')
	{
		printf("%c", str[i]);
		i++;
	}
	printf("\n");
	return (i);
}

int	read_token(t_env *utils)
{
	int		i;
	int		j;

	i = 0;
	while (utils->line[i])
	{
		j = 0;
		remove_space(utils->line, &i);
		if (is_token(utils->line[i]) == TRUE)
			j = handle_token(utils->line, i);
		else
			j = handle_word(utils->line, i);
		if (j < 0)
			return (0);
		i += j;
	}
	return (1);
}