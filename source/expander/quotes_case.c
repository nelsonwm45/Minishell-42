/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_case.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:51:06 by nchok             #+#    #+#             */
/*   Updated: 2024/12/02 17:17:38 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*expand_decision(t_general *utils, char *str)
{
	char	*new;
	int		i;

	i = 0;
	utils->found_quote = 0;
	utils->last_q_i = -1;
	new = ft_strdup("\0");
	while (str[i])
	{
		if (!utils->found_quote && (str[i] == '\'' || str[i] == '\"'))
			process_unquoted(utils, str, &i, &new);
		else if (utils->found_quote && utils->found_quote == str[i])
			process_quoted(utils, str, &i, &new);
		i++;
	}
	if (utils->last_q_i < (i - 1))
		process_end(utils, str, &i, &new);
	return (new);
}

int	process_unquoted(t_general *utils, char *str, int *i, char **new)
{
	char	*tmp;
	char	*tmp2;

	if (*i != 0)
	{
		tmp = ft_substr(str, utils->last_q_i + 1, *i - utils->last_q_i - 1);
		tmp2 = replace_to_env(utils, tmp);
		free(tmp);
		*new = ft_strjoin(*new, tmp2);
		free(tmp2);
	}
	utils->found_quote = str[*i];
	utils->last_q_i = *i;
	return (0);
}

int	process_quoted(t_general *utils, char *str, int *i, char **new)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(str, utils->last_q_i + 1, *i - utils->last_q_i - 1);
	if (utils->found_quote == '\"')
	{
		tmp2 = replace_to_env(utils, tmp);
		free(tmp);
		*new = ft_strjoin(*new, tmp2);
		free(tmp2);
	}
	else
	{
		*new = ft_strjoin(*new, tmp);
		free(tmp);
	}
	utils->found_quote = 0;
	utils->last_q_i = *i;
	return (0);
}

int	process_end(t_general *utils, char *str, int *i, char **new)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(str, utils->last_q_i + 1, *i - utils->last_q_i - 1);
	tmp2 = replace_to_env(utils, tmp);
	free(tmp);
	*new = ft_strjoin(*new, tmp2);
	free(tmp2);
	return (0);
}
