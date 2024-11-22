/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:52:07 by nchok             #+#    #+#             */
/*   Updated: 2024/11/22 10:39:03 by hheng            ###   ########.fr       */
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
	int		k;
	int		equal_i;
	int		var_len;
	char	*tmp2;
	char	*tmp3;
	char	var_name[256]; // Buffer for the variable name

	k = 0;
	var_len = 0;

	// Extract the variable name from str[j + 1]
	while (str[j + 1 + var_len] && (ft_isalnum(str[j + 1 + var_len]) || str[j + 1 + var_len] == '_'))
		var_len++;

	// If there's no valid variable name after $, skip it
	if (var_len == 0)
		return (1); // Skip the $

	// Copy the variable name into var_name
	ft_strlcpy(var_name, &str[j + 1], var_len + 1); // +1 for null terminator
	printf("[DEBUG] Extracted variable name: %s\n", var_name);

	// Search for the variable in the environment variables
	while (utils->envp[k])
	{
		printf("[DEBUG] envp[%d]: '%s'\n", k, utils->envp[k]);
		equal_i = get_equal_sign_index(utils->envp[k]);
		if (equal_i > 0)
		{
			// Compare the variable name exactly (considering its length)
			if (ft_strncmp(utils->envp[k], var_name, var_len) == 0 && utils->envp[k][var_len] == '=')
			{
				printf("[DEBUG] Match found: '%s'\n", utils->envp[k]);
				tmp2 = ft_strdup(utils->envp[k] + var_len + 1);
				if (!tmp2)
				{
					fprintf(stderr, "[ERROR] Memory allocation failed for tmp2\n");
					return (0);
				}
				tmp3 = ft_strjoin(*tmp, tmp2);
                if (!tmp3)
                {
                    fprintf(stderr, "[ERROR] Memory allocation failed for tmp3\n");
                    return (0);
                }
				free(*tmp);
				*tmp = tmp3;
				free(tmp2);
				return (var_len + 1);
			}
		}
		k++;
	}

	// If variable not found, skip it
	printf("[DEBUG] Variable not found: %s\n", var_name);
	return (var_len + 1); // Skip past the variable name and $
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

    printf("[DEBUG] Starting replace_to_env with input str: %s\n", str);
    if (!tmp)
    {
        fprintf(stderr, "[ERROR] Memory allocation failed for tmp\n");
        return NULL;
    }

    while (str[j])
    {
        printf("[DEBUG] Current character: %c, index: %d\n", str[j], j);

        // Skip characters after dollar if they are digits
        j += skipped_char_after_dollar(j, str);

        // Handle "$?"
        if (str[j] == '$' && str[j + 1] == '?')
        {
            printf("[DEBUG] Found $? at index: %d\n", j);
            j += replace_question_mark(utils, &tmp);
            if (!tmp)
            {
                fprintf(stderr, "[ERROR] replace_question_mark failed\n");
                return NULL;
            }
            printf("[DEBUG] tmp after $? replacement: %s\n", tmp);
        }
        // Handle "$" followed by variable names
        else if (str[j] == '$' && (str[j + 1] != ' ' &&
                 (str[j + 1] != '"' || str[j + 2] != '\0')) &&
                 str[j + 1] != '\0')
        {
            printf("[DEBUG] Found variable starting with $ at index: %d\n", j);
            j += subs_dollar_var(utils, str, &tmp, j);
            if (!tmp)
            {
                fprintf(stderr, "[ERROR] subs_dollar_var failed or returned NULL\n");
                return NULL;
            }
            printf("[DEBUG] tmp after variable replacement: %s\n", tmp);
        }
        // Handle other characters
        else
        {
            printf("[DEBUG] Appending character to tmp at index: %d\n", j);
            j = append_str(&tmp, &tmp2, &tmp3, j);
            if (!tmp)
            {
                fprintf(stderr, "[ERROR] append_str failed\n");
                return NULL;
            }
            printf("[DEBUG] tmp after append: %s\n", tmp);
        }
    }

    printf("[DEBUG] Final expanded string: %s\n", tmp);
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
