/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:52:07 by nchok             #+#    #+#             */
/*   Updated: 2024/11/13 15:55:56 by nchok            ###   ########.fr       */
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
		1. get the str after dollar sign & concatenante
		2. return length of the string till the "equal sign" + 1 if found matched env variable
		3. return the length of str after the dollar sign if no matched env variable found
*/
int	subs_dollar_var(t_general *utils, char *str, char **tmp, int j)
{
	int	k;
	int	equal_i;
	int	ret_val;
	char	*tmp2;
	char	*tmp3;

	k = 0;
	while (utils->envp[k])
	{
		equal_i = get_equal_sign_index(utils->envp[k]);
		if (ft_strncmp(utils->envp[k], &str[j + 1], equal_i - 1) == 0 
			&& equal_i == (dollar_str_len(str, j) - j))
		{
			tmp2 = ft_strdup(utils->envp[k] + equal_i);
			tmp3 = ft_strjoin(*tmp, tmp2);
			free(*tmp);
			*tmp = tmp3;
			free(tmp2);
			ret_val = equal_i;
		}
		k++;
	}
	if (ret_val == 0)
		ret_val = dollar_str_len(str, j) - j;
	return (ret_val);
}

/*
	@todo
		1. Put back the if statement to skipped char after dollar
		2. Move the else statement to a function

	@brief
		check current char is $
			1. if next char is digit, skipped the digit
			2. if next char is ?, replace the current str with the exit status
			3. if next char is str, 
				->check if matched env variable, replace the current str with the env value
				->if not matched, get the length of the str after the dollar sign

		if the current is not $ || the next char after $ is digit, concatenate the current char to the str

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
		j += skipped_char_after_dollar(j, str); // skip the char if current char is $ and next char is digit
		if (str[j] == '$' && str[j + 1] == '?') // current char is $, next is ?
			j += replace_question_mark(utils, &tmp); // replace the current str with the exit status
		else if (str[j] == '$' && (str[j + 1] != ' ' && (str[j + 1] != '"'
					|| str[j + 2] != '\0')) && str[j + 1] != '\0') // current char is $, next is not space or quote
			j += subs_dollar_var(utils, str, &tmp, j);
		else
			j = append_str(&tmp, &tmp2, &tmp3, j); // concatenate the current char to the str
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

/*
	@brief
		1. expand single quotes
		2. remove single quotes
		3. remove double quotes
*/
char	*expand_str(t_general *utils, char *str)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	i = find_dollar(str); // index after dollar sign
	while (str[i - 2] == '\'' && i != 0 && str[i] != '\0') // check if the current char is in single quotes
	{
		tmp = replace_to_env(utils, str); // replace the current str with the env value
		free(str); // free the old str memory
		str = tmp; // assign the new str to the old str
	}
	str = remove_quotes(str, '\''); // remove the single quotes
	str = remove_quotes(str, '\"'); // remove the double quotes
	return (str);
}
