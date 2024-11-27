/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:43:07 by nchok             #+#    #+#             */
/*   Updated: 2024/11/27 17:35:15 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	find_next_quote(char *line, int *i, int *num_quote, char quote)
{
	int	j;

	j = *i + 1;
	while (line[j])
	{
		if (line[j] == quote)
		{
			(*num_quote)++;
			break ;
		}
		j++;
	}
	*i = j;
	return (0);
}

int	closed_quotes(char *line)
{
	int	i;
	int	sing_q;
	int	doub_q;

	i = 0;
	sing_q = 0;
	doub_q = 0;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			sing_q++;
			find_next_quote(line, &i, &sing_q, '\'');
		}
		if (line[i] == '\"')
		{
			doub_q++;
			find_next_quote(line, &i, &doub_q, '\"');
		}
		i++;
	}
	if (sing_q % 2 == 1 || doub_q % 2 == 1)
		return (FALSE);
	return (TRUE);
}
