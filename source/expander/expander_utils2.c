/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:52:59 by nchok             #+#    #+#             */
/*   Updated: 2024/11/13 14:38:39 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../header/minishell.h"

/*
	@brief
		return the number of char needs to skip if current char is $ and next char is digit
		0 - if no dollar sign found
		1 - if dollar sign found but next char not digit
		2 - if dollar sign found and next char is digit
*/
int		skipped_char_after_dollar(int j, char *str)
{
	int		i;

	i = j; // save the initial index
	if (str[j] == '$') // check if current char is '$'
	{
		if (ft_isdigit(str[j + 1])) // check if the char after '$' is a digit
			j += 2; // skip the digit and dollar sign
	}
	return (j - i); // return the number of char need to skip
}

/*
	append the char to the str
*/
int	append_str(char **tmp, char **tmp2, char **tmp3, int j)
{
	*tmp2 = char_to_str(j);
	*tmp3 = ft_strjoin(*tmp, *tmp2);
	free(*tmp);
	*tmp = *tmp3;
	free(*tmp2);
	return (j++);
}

/*
	@brief
		remove the quotes from the str

	found the quote
		1. entered the loop
		2. shift the str to the left
		3. add null character at the end

	@examples
		1. remove_quotes("hello", '\"') -> "hello"
		2. remove_quotes("\"hello\"", '\"') -> "hello"
		3. remove_quotes("'hello'", '\'') -> "hello"
		4. remove_quotes("\"hello", '\"') -> "hello"
		5. remove_quotes("'hello", '\'') -> "hello"
		6. remove_quotes("hello\"", '\"') -> "hello"
		7. remove_quotes("hello'", '\'') -> "hello"
	
*/
char *remove_quotes(char *str, char quote)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;

	i = 0;
	while (str[i])
	{
		if (str[i] == quote)
		{
			j = i;
			while (str[j + 1])
			{
				str[j] = str[j + 1];
				j++;
			}
			str[j] = '\0';
		}
		else
			i++;
	}
	return (str);
}