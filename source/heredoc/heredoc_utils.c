/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 02:20:36 by nchok             #+#    #+#             */
/*   Updated: 2024/11/27 17:26:45 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*check_if_var(t_general *utils, char *line)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	tmp = ft_strdup("\0");
	while (line[i])
	{
		j = i;
		if (line[i] == '$' && line[i + 1] != ' ' && line[i + 1] != '\0')
		{
			j += subs_dollar_var(utils, line, &tmp, i);
			i = j;
		}
		else
			i = append_str(&tmp, line[i], i);
	}
	line = tmp;
	return (line);
}
