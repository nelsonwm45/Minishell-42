/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:26:26 by hheng             #+#    #+#             */
/*   Updated: 2024/11/05 13:26:26 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
@brief : Calculates the total length of all the strings in a linked list of
		environment variables (t_env) plus the newline characters between them.

1. Start with lst_len = 0 to keep track of the total size.
2. Go through each node in the environment list (t_env):
3. If the value (the environment variable) is not empty, 
	add its length to lst_len.
4. Add 1 more space for a newline character (\n) to separate it from the 
	next variable.
5. Stop when you reach the end of the list (lst->next == NULL).
6. Return the total size you calculated.
*/
size_t	size_env(t_env *lst)
{
	size_t	lst_len;

	lst_len = 0;
	while (lst && lst->next != NULL)
	{
		if (lst->value != NULL)
		{
			lst_len += ft_strlen(lst->value);
			lst_len++;
		}
		lst = lst->next;
	}
	return (lst_len);
}

/*
@brief : t combines all the environment variables into 
		a single string, with each variable separated by a newline (\n).
exp: 
- Copy "USER=root" into the string → Add a newline (\n).
- Copy "HOME=/root" after it → Add a newline (\n).
- Copy "PATH=/bin" last, with no newline.
*/
char	*env_to_str(t_env *lst)
{
	char	*env;
	int		i;
	int		j;

	env = malloc(sizeof(char) * size_env(lst) + 1);
	if (!env)
		return (NULL);
	i = 0;
	while (lst && lst->next)
	{
		if (lst->value)
		{
			j = -1;
			while (lst->value[++j])
				env[i++] = lst->value[j];
		}
		if (lst->next->next)
			env[i++] = '\n';
		lst = lst->next;
	}
	env[i] = '\0';
	return (env);
}
