/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_case.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:51:06 by nchok             #+#    #+#             */
/*   Updated: 2024/12/02 02:56:49 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

// char	*expand_decision(t_general *utils, char *str)
// {
// 	int		open;
// 	int		close;
// 	char	outer;
// 	char	inner;
// 	char	*tmp;
// 	char	*tmp2;
// 	char	*final;
// 	int		len;
	
// 	open = 0;
// 	close = 0;
// 	tmp2 = ft_strdup("\0");
// 	final = ft_strdup("\0");
// 	while (str[open])
// 	{
//		printf("strlen: %zu\n", ft_strlen(str + open + 1));
// 		if (str[open] == '\"' && next_quote(str, open + 1, '\"', ft_strlen(str + open + 1)) != 0)
// 		{
// 			printf("Here\n");
// 			close = next_quote(str, open + 1, '\"', ft_strlen(str + open + 1));
// 			outer = '\"';
// 			inner = is_quote(str[open + 1]);
// 			printf("open: %d\n", open);
// 			printf("close: %d\n", close);
// 			if (close == open + 1)
// 				open += 2;
// 			else if (inner != 0 && next_quote(str, open + 1, inner, close - open) != 0)
// 			{
// 				printf("HELLLLOOOWWW\n");
// 				tmp = ft_substr(str, open + 1, close - open - 1);
// 				printf("tmp: %s\n", tmp);
// 				tmp2 = replace_to_env(utils, tmp);
// 				free(tmp);
// 				printf("open: %d\n", open);
// 				printf("close: %d\n", close);
// 				tmp2 = remove_specific_quotes(tmp2, outer, open, close);
// 				open += close + 1;
// 			}
// 			else
// 			{
// 				tmp = ft_substr(str, open + 1, close - open - 1);
// 				printf("tmp: %s\n", tmp);
// 				tmp2 = replace_to_env(utils, tmp);
// 				free(tmp);
// 				printf("open: %d\n", open);
// 				printf("close: %d\n", close);
// 				tmp2 = remove_specific_quotes(tmp2, outer, open, close);
// 				open += close + 1;
// 			}
// 		}
// 		else if (str[open] == '\'' && next_quote(str, open + 1, '\'', ft_strlen(str + open + 1)) != 0)
// 		{
// 			outer = '\'';
// 			close = next_quote(str, open + 1, '\'', ft_strlen(str + open + 1));
// 			tmp2 = ft_substr(str, open + 1, close - open - 1);
// 			printf("tmp2: %s\n", tmp2);
// 			tmp2 = remove_specific_quotes(tmp2, outer, open, close);
// 			open += close + 1;
// 		}
// 		else
// 		{
// 			tmp2 = replace_to_env(utils, str + open);
// 			open += ft_strlen(str + open);
// 		}
// 		printf("tmp2: %s\n", tmp2);
// 		printf("tmp2 remove quotes: %s\n", tmp2);
// 		final = ft_strjoin(final, tmp2);
// 		printf("final: %s\n", final);
// 		printf("~~~~~~~~~~~next string~~~~~~~~~~~\n");
// 		free(tmp2);
// 	}
// 	return (final);
// }

char *expand_decision(t_general *utils, char *str)
{
    int     open;
    int     close;
    char    *tmp;
    char    *tmp2;
    char    *final;
    
    open = 0;
    final = ft_strdup("");
    while (str[open])
    {
        if (str[open] == '\"' && next_quote(str, open + 1, '\"', ft_strlen(str + open + 1)) != 0)
        {
            close = next_quote(str, open + 1, '\"', ft_strlen(str + open + 1));
            
            if (close == open + 1)
            {
                // Empty quotes case
                tmp2 = ft_strdup("");
                final = ft_strjoin(final, tmp2);
                free(tmp2);
                open += 2;
            }
            else
            {
                // Extract content within quotes, expand environment variables
                tmp = ft_substr(str, open + 1, close - open - 1);
                tmp2 = replace_to_env(utils, tmp);
                free(tmp);
                final = ft_strjoin(final, tmp2);
                free(tmp2);
                open = close + 1;
            }
        }
        else if (str[open] == '\'' && next_quote(str, open + 1, '\'', ft_strlen(str + open + 1)) != 0)
        {
            close = next_quote(str, open + 1, '\'', ft_strlen(str + open + 1));
            
            if (close == open + 1)
            {
                // Empty quotes case
                tmp2 = ft_strdup("");
                final = ft_strjoin(final, tmp2);
                free(tmp2);
                open += 2;
            }
            else
            {
                // Extract content within single quotes without expansion
                tmp2 = ft_substr(str, open + 1, close - open - 1);
                final = ft_strjoin(final, tmp2);
                free(tmp2);
                open = close + 1;
            }
        }
        else
        {
            // Handle non-quote characters or environment variable expansion
            tmp2 = replace_to_env(utils, str + open);
            final = ft_strjoin(final, tmp2);
            free(tmp2);
            open += ft_strlen(str + open);
        }
    }
    return (final);
}

int	next_quote(char *str, int i, char quote, int len)
{
	int	close;

	close = 0;
	while (str[i] && i <= len)
	{
		if (str[i] == quote)
		{
			close = i;
			return (close);
		}
		i++;
	}
	return (close);
}

char	is_quote(char c)
{
	if (c == '\"' || c == '\'')
		return (c);
	return (0);
}

char	*remove_specific_quotes(char *str, char quote, int open, int close)
{
	int	i;
	
	if (str[open] == quote)
	{
		i = open;
		while (str[open])
		{
			str[open] = str[open + 1];
			open++;
		}
		str[open] = '\0';
		open = i;
	}
	if (str[close - 1] == quote)
		str[close] = '\0';
	return (str);
}
