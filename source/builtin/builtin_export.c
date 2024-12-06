/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:45:05 by hheng             #+#    #+#             */
/*   Updated: 2024/10/30 13:45:05 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Check if the variable is valid
static int	print_error(int error, const char *arg)
{
	int		i;

	if (error == -1)
		ft_putstr_fd("export: not valid in this context: ", 2);
	else if (error == 0 || error == -3)
		ft_putstr_fd("export: not a valid identifier: ", 2);
	i = 0;
	while (arg[i] && (arg[i] != '=' || error == -3))
	{
		write(2, &arg[i], 1);
		i++;
	}
	write(2, "\n", 1);
	return (1);
}

/*
1. Adds a new environment variable to the linked list `env`
- If the first node is empty, add the value there
- Allocate memory for the new environment variable node
- Duplicate the value string and add it to the new node
- save the reference to the last node
- inset to new node then link it to the rest
*/
int	env_add(const char *value, t_env *env)
{
	t_env	*new;
	t_env	*tmp;

	if (env && env->value == NULL)
	{
		env->value = ft_strdup(value);
		return (SUCCESS);
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return (-1);
	new->value = ft_strdup(value);
	while (env && env->next && env->next->next)
		env = env->next;
	tmp = env->next;
	env->next = new;
	new->next = tmp;
	return (SUCCESS);
}

/*
1. Extracts the name part of an environment variable
(before the '=')
- Copy characters from `src` to `dest` until '=' or
	end of string
*/
char	*get_env_name(char *dest, const char *src)
{
	int		i;

	i = 0;
	while (src[i] && src[i] != '=' && ft_strlen(src) < BUFF_SIZE)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/*
- Checks if a given variable already exists in the environment
- If it exists, updates its value; otherwise, returns 0
- Extract the variable name from `args` KEY=VALUE (name)
- Extract the name from the current `env` node
- return 1 indicate updated & found
*/
int	is_in_env(t_env *env, char *args)
{
	char	var_name[BUFF_SIZE];
	char	env_name[BUFF_SIZE];

	get_env_name(var_name, args);
	while (env && env->next)
	{
		get_env_name(env_name, env->value);
		if (ft_strcmp(var_name, env_name) == 0)
		{
			ft_memdel(env->value);
			env->value = ft_strdup(args);
			return (1);
		}
		env = env->next;
	}
	return (SUCCESS);
}

int	ft_export(char **args, t_env *env, t_env *secret)
{
	int	error_ret;
	int	new_env;
	int	i;
	int	status;

	if (!args[1])
		return (print_sorted_env(secret), SUCCESS);
	i = 0;
	status = SUCCESS;
	while (args[++i])
	{
		error_ret = is_valid_env(args[i]);
		if (args[i][0] == '=' || error_ret <= 0)
		{
			status = print_error(error_ret, args[i]);
			continue ;
		}
		new_env = is_in_env(env, args[i]);
		if (error_ret != 2 && !new_env)
			env_add(args[i], env);
		else if (error_ret == 2)
			env_add(args[i], secret);
	}
	return (status);
}
