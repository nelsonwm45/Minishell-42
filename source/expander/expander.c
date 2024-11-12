/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:52:07 by nchok             #+#    #+#             */
/*   Updated: 2024/11/12 17:57:40 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"


t_cmds	*call_expander(t_general *utils, t_cmds *cmds)
{
	t_lexer	*ptr;

	cmds->str = expander(utils, cmds->str);
	ptr = cmds->redir;
	while (ptr)
	{
		if (ptr->token_type != SMALLSMALL)
			ptr->str = expand_str(utils, ptr->str);
		ptr = ptr->next;
	}
	ptr = cmds->redir;
	return (cmds);
}

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



int	loop_if_dollar_sign(t_general *utils, char *str, char **tmp, int j)
{
	int	k;
	char	*tmp2;
	char	*tmp3;

	k = 0;
	while (utils->envp[k])
	{
		if (ft_strncmp(utils->envp[k], &str[j + 1], get_equal_sign_index(utils->envp[k]) - 1) == 0)
		{
			tmp2 = ft_strdup(utils->envp[k] + get_equal_sign_index(utils->envp[k]));
			tmp3 = ft_strjoin(*tmp, tmp2);
			free(*tmp);
			*tmp = tmp3;
			free(tmp2);
		}
		k++;
	}
}

/*
	
*/
char	*replace_to_env(t_general *utils, char *str)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = 0;
	tmp = ft_strdup("\0");
	while (str[j])
	{
		j += skipped_char_after_dollar(j, str);
		if (str[j] == '$' && str[j + 1] == '?') // current char is $, next is ?
			j += replace_question_mark(utils, &tmp); // replace the current str with the exit status
		else if (str[j] == '$' && (str[j + 1] != ' ' && (str[j + 1] != '"'
					|| str[j + 2] != '\0')) && str[j + 1] != '\0')
			j += loop_if_dollar_sign(utils, str, &tmp, j);
		else
		{
			tmp2 = char_to_str(str[j++]);
			tmp3 = ft_strjoin(tmp, tmp2);
			free(tmp);
			tmp = tmp3;
			free(tmp2);
		}
	}
	return (tmp);
}

/*
	@brief
		1. check if the current char is not in single quotes && current str need to have dollar && the cha after dollar is not null character
			replace the current str with the env value
		2. remove quotes if the current command is not export

	returns
		- str

*/
char	**expander(t_general *utils, char **str)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	temp = NULL;
	while (str[i])
	{
		j = find_dollar(str[i]); // get the index of cha after dollar sign
		if (str[i][j - 2] != '\'' && j != 0 && str[i][j] != '\0') // check if the current char is not in single quotes
		{
			temp = replace_to_env(utils, str[i]); 
			free(str[i]); // free old str memory
			str[i] = temp; 
		}
		if (ft_strncmp(str[0], "export", ft_strlen(str[0]) - 1) != 0) // remove quotes if not export
		{
			str[i] = remove_quotes(str[i], '\"');
			str[i] = remove_quotes(str[i], '\'');
		}
		i++;
	}
	return (str);
}

