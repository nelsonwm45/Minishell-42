/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:52:07 by nchok             #+#    #+#             */
/*   Updated: 2024/11/27 16:50:51 by nchok            ###   ########.fr       */
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
	@brief : substitutes a variable prefixed with $ in the input string str
	 with its value from the environment variables linked list.

	 exp : 
	 Get Variable Name Length:

1. Variable name = "USER".
2. var_len = 4.
3. Iterate Through Environment Variables:

4. Find "USER=root" where the name matches "USER".
5. Substitute Value:

	tmp2 = strdup("root");
	tmp3 = strjoin("Hello ", "root");
	Result: "Hello root".
	Free old tmp and update it with "Hello root".
Return:
	Return 5 (var_len + 1)

*/
int	subs_dollar_var(t_general *utils, char *str, char **tmp, int j)
{
	int		equal_i;
	int		var_len;
	t_env	*ptr;
	char	*tmp2;
	char	*tmp3;

	var_len = get_var_equal_len(str, j);
	ptr = utils->mini->env_vars;
	while (ptr)
	{
		equal_i = get_equal_sign_index(ptr->value);
		if (equal_i > 0 && ft_strncmp(ptr->value, &str[j + 1], var_len) == 0
			&& ptr->value[var_len] == '=')
		{
			tmp2 = ft_strdup(ptr->value + equal_i);
			tmp3 = ft_strjoin(*tmp, tmp2);
			free(*tmp);
			*tmp = tmp3;
			free(tmp2);
			return (var_len + 1);
		}
		ptr = ptr->next;
	}
	return (var_len + 1);
}

/*
	@todo
		1. Put back the if statement to skipped char after dollar
		2. Move the else statement to a function

	@brief
		check current char is $
			1. if next char is digit, skipped the digit
			2. if next char is ?, replace the current str 
				with the exit status
			3. if next char is str, 
				->check if matched env variable, 
					replace the current str with the env value
				->if not matched, get the length 
					of the str after the dollar sign

		if the current is not $ || the next char after $ is digit, 
			concatenate the current char to the str

*/
char	*replace_to_env(t_general *utils, char *str)
{
	int		j;
	char	*tmp;

	tmp = ft_strdup("\0");
	j = 0;
	while (str[j])
	{
		j += skipped_char_after_dollar(j, str);
		if (str[j] == '$' && str[j + 1] == '?')
			j += replace_question_mark(utils, &tmp);
		else if (str[j] == '$' && (str[j + 1] != ' '
				&& (str[j + 1] != '"' || str[j + 2] != '\0'))
			&& str[j + 1] != '\0')
			j += subs_dollar_var(utils, str, &tmp, j);
		else
			j = append_str(&tmp, str[j], j);
	}
	return (tmp);
}

/*
	@brief
		1. check if the current char is not in single quotes && 
			current str need to have dollar && 
			the cha after dollar is not null character
				-replace the current str with the env value
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
		j = find_dollar(str[i]);
		if (str[i][j - 2] != '\'' && j != 0 && str[i][j] != '\0')
		{
			temp = replace_to_env(utils, str[i]);
			free(str[i]);
			str[i] = temp;
		}
		if (ft_strncmp(str[0], "export", ft_strlen(str[0]) - 1) != 0)
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
	i = find_dollar(str);
	while (str[i - 2] == '\'' && i != 0 && str[i] != '\0')
	{
		tmp = replace_to_env(utils, str);
		free(str);
		str = tmp;
	}
	str = remove_quotes(str, '\'');
	str = remove_quotes(str, '\"');
	return (str);
}
