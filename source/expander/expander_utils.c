/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:30:15 by nchok             #+#    #+#             */
/*   Updated: 2024/11/27 16:43:11 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/*
	@brief
		return the index of character after dollar sign
		return 0 if dollar sign is not found
	
*/
int	find_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (i + 1);
		i++;
	}
	return (i);
}

/*
	@brief
		1. 
		2. return the length of the exit status (in ascii) + 1
		e.g -> 123 -> 3 + 1 = 4
*/
int	replace_question_mark(t_general *utils, char **tmp)
{
	int	len;

	len = 0;
	free(*tmp);
	*tmp = ft_itoa(utils->exit_status);
	len = ft_strlen(*tmp);
	return (len + 1);
}

/*
	@brief
	1. return the index of the equal sign + 1
	2. return 0 if equal sign is not found
*/
int	get_equal_sign_index(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i + 1);
		i++;
	}
	return (0);
}

/*
	@brief
		find the length of a substring that ends at any of these characters
*/
int	dollar_str_len(char *str, int j)
{
	int	len;

	len = j;
	while (str[len] != ' ' && str[len] != '\0' && str[len] != '$'
		&& str[len] != '\"' && str[len] != '\'' && str[len] != '='
		&& str[len] != ':' && str[len] != '-')
		len++;
	return (len);
}

/*
	@brief
		make a string from a character
*/
char	*char_to_str(char c)
{
	char	*str;

	str = ft_calloc(2, sizeof(char));
	str[0] = c;
	return (str);
}
