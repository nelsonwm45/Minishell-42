/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:52:07 by nchok             #+#    #+#             */
/*   Updated: 2024/11/22 15:46:45 by hheng            ###   ########.fr       */
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
int subs_dollar_var(t_general *utils, char *str, char **tmp, int j)
{
    int k;
    int equal_i;
    int var_len;
    char *tmp2;
    char *tmp3;

    k = 0;
    // Calculate variable length first
    var_len = 0;
    while (str[j + 1 + var_len] && (ft_isalnum(str[j + 1 + var_len]) || str[j + 1 + var_len] == '_'))
        var_len++;

    // If no valid variable name after $, skip it
    if (var_len == 0)
        return (1);

    printf("[DEBUG] Variable name length: %d, name: %.*s\n", var_len, var_len, &str[j + 1]);

    // Debug: Print envp before searching
    printf("[DEBUG] Current envp:\n");
    for (int i = 0; utils->envp[i] != NULL; i++) {
        printf("envp[%d]: %s\n", i, utils->envp[i]);
    }

    while (utils->envp[k])
    {
        equal_i = get_equal_sign_index(utils->envp[k]);
        // Compare only the variable name part and check for exact match
        if (equal_i > 0 && strncmp(utils->envp[k], &str[j + 1], var_len) == 0 
            && utils->envp[k][var_len] == '=')
        {
            // Get value after '=' sign
            tmp2 = ft_strdup(utils->envp[k] + equal_i + 1);
            if (!tmp2)
            {
                fprintf(stderr, "[ERROR] Memory allocation failed for tmp2\n");
                return (0);
            }
            tmp3 = ft_strjoin(*tmp, tmp2);
            if (!tmp3)
            {
                fprintf(stderr, "[ERROR] Memory allocation failed for tmp3\n");
                free(tmp2);
                return (0);
            }
            free(*tmp);
            *tmp = tmp3;
            free(tmp2);
            printf("[DEBUG] Substituted value: %s\n", *tmp);
            return (var_len + 1);
        }
        k++;
    }

    // If variable not found, skip the name
    printf("[DEBUG] Variable '%.*s' not found in envp\n", var_len, &str[j + 1]);
    return (var_len + 1);
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
char *replace_to_env(t_general *utils, char *str)
{
    int j = 0;
    char *tmp = ft_strdup("\0"); // Initialize tmp as an empty string
    char *tmp2 = NULL;
    char *tmp3 = NULL;

    if (!tmp)
    {
        fprintf(stderr, "[ERROR] Memory allocation failed for tmp\n");
        return NULL;
    }

    while (str[j])
    {

        // Skip characters after dollar if they are digits
        j += skipped_char_after_dollar(j, str);

        // Handle "$?"
        if (str[j] == '$' && str[j + 1] == '?')
        {
            j += replace_question_mark(utils, &tmp);
            if (!tmp)
            {
                fprintf(stderr, "[ERROR] replace_question_mark failed\n");
                return NULL;
            }
        }
        // Handle "$" followed by variable names
        else if (str[j] == '$' && (str[j + 1] != ' ' &&
                 (str[j + 1] != '"' || str[j + 2] != '\0')) &&
                 str[j + 1] != '\0')
        {
            
            j += subs_dollar_var(utils, str, &tmp, j);
            if (!tmp)
            {
                fprintf(stderr, "[ERROR] subs_dollar_var failed or returned NULL\n");
                return NULL;
            }
        }
        // Handle other characters
        else
        {
            j = append_str(&tmp, &tmp2, &tmp3, j);
            if (!tmp)
            {
                fprintf(stderr, "[ERROR] append_str failed\n");
                return NULL;
            }
        }
    }

    return tmp;
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
		if (str[i][j - 2] != '\'' && j != 0 && str[i][j] != '\0') 
		{
			temp = replace_to_env(utils, str[i]); 
			free(str[i]); // free old str memory
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
