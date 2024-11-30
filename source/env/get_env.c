/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:27:38 by hheng             #+#    #+#             */
/*   Updated: 2024/11/05 13:27:38 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@brief : Checks if the string is a valid environment variable.

1. If the first character is a digit (ft_isdigit returns 1), 
	it’s invalid → Return 0.
2. Iterate through each character before the = sign:
3. If any character is not alphanumeric (ft_isalnum returns 0), 
	return -1 (invalid).
4. If the string does not contain an = at all, return 2 (missing =).
5. If all checks pass, return 1 (valid).
*/
int	is_valid_env(const char *env)
{
	int	i;

	i = 0;
	if (ft_isdigit(env[i]) == 1)
		return (0);
	while (env[i] && env[i] != '=')
	{
		if (ft_isalnum(env[i]) == 0)
			return (-1);
		i++;
	}
	if (env[i] != '=')
		return (2);
	return (1);
}

/*
@brief : Calculates the length of the value part 
	of the environment variable (everything after the = sign).

- Start counting characters after =
*/
int	env_value_len(const char *env)
{
	int	i;
	int	size_name;

	size_name = 0;
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	i += 1;
	while (env[i])
	{
		i++;
		size_name++;
	}
	return (size_name);
}

/*
@brief : Extracts and returns the value part
	 (everything after =) from an environment variable.

1. Calculate how much memory is needed for the 
	value (env_value_len(env) + 1 for \0).
2. Allocate memory for the value string.
3. Find the position of = and start copying characters after =.
4. Add a \0 at the end to terminate the string.
5. Return the value string.
*/
char	*env_value(char *env)
{
	int		i;
	int		j;
	int		size_alloc;
	char	*env_value;

	size_alloc = env_value_len(env) + 1;
	env_value = malloc(sizeof(char) * size_alloc);
	if (!env_value)
		return (NULL);
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	i += 1;
	j = 0;
	while (env[i])
	{
		env_value[j] = env[i];
		j++;
		i++;
	}
	env_value[j] = '\0';
	return (env_value);
}

/*
@brief: Searches for a specific environment variable 
	by name and returns its value.

1. Create a buffer (env_name) to hold the name part of 
	the current environment variable.
2. Start with an empty string for env_val.
3. Loop through the environment list (t_env):
-  Extract the name part using get_env_name.
- Compare the name (arg) with the current environment 
	variable’s name.
- If it matches:
	-Free the current env_val.
	-Extract the value using env_value and return it.
4. If no match is found, return the empty string.

*/
char	*get_env_value(char *arg, t_env *env)
{
	char	env_name[BUFF_SIZE];
	char	*env_val;

	env_val = ft_strdup("");
	while (env && env->value)
	{
		get_env_name(env_name, env->value);
		if (ft_strcmp(arg, env_name) == 0)
		{
			ft_memdel(env_val);
			env_val = env_value(env->value);
			return (env_val);
		}
		env = env->next;
	}
	return (env_val);
}
