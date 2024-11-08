/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:06:11 by hheng             #+#    #+#             */
/*   Updated: 2024/11/05 18:06:11 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int get_var_len(const char *arg, int i, t_env *env, int ret)
{
    int len = 0;
    t_env *current_env;

    if (arg[i] == '?')
    {
        // Handle special case for $? which represents the last return code
        len = ft_numlen(ret); // Assuming ft_numlen is a function that returns the length of a number
    }
    else
    {
        // Handle regular environment variables
        current_env = env;
        while (current_env)
        {
            if (ft_strncmp(current_env->value, arg + i, ft_strlen(arg + i)) == 0 && current_env->value[ft_strlen(arg + i)] == '=')
            {
                len = ft_strlen(current_env->value + ft_strlen(arg + i) + 1);
                break;
            }
            current_env = current_env->next;
        }
    }
    return len;
}

int		arg_alloc_len(const char *arg, t_env *env, int ret)
{
	int		i;
	int		size;

	i = -1;
	size = 0;
	while (arg[++i])
	{
		if (arg[i] == '$')
		{
			i++;
			if ((arg[i] == '\0' || ft_isalnum(arg[i]) == 0) && arg[i] != '?')
				size++;
			else
				size += get_var_len(arg, i, env, ret);
			if (ft_isdigit(arg[i]) == 0)
			{
				while (arg[i + 1] && is_env_char(arg[i]))
					i++;
			}
			else
				size--;
		}
		size++;
	}
	return (size);
}


