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
	return (ERROR);
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

<<<<<<< HEAD
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
=======
    if (!env)
        return (-1);

    if (env->value == NULL)
    {
        env->value = ft_strdup(value);
        env->next = NULL;
        return (SUCCESS);
    }
    if (!(new = malloc(sizeof(t_env))))
        return (-1);
    new->value = ft_strdup(value);
    new->next = NULL;
    tmp = env;
    while (tmp->next)
        tmp = tmp->next;

    tmp->next = new;
    return (SUCCESS);
>>>>>>> origin/check
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

<<<<<<< HEAD
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
=======
    get_env_name(var_name, args);

   ptr = env;
    while (env)
    {
        if (env->value)
        {
            get_env_name(env_name, env->value);
            if (ft_strcmp(var_name, env_name) == 0)
            {
                free(env->value);
                env->value = ft_strdup(args);
                return (1);
                }
        }
        env = env->next;
    }
    env = ptr;
    return (0);
>>>>>>> origin/check
}

/*
- Handles the `export` command for the shell
- Adds or updates variables in the environment or secret lis
-
- Print an error if the variable is invalid and return
- Check if the variable already exists in the environment
- if no , add it to the list
- error_ret = 0, invalid
- error_ret = 1, valid , add or update
- error_ret = 2, valid , but only KEY part
*/
int	ft_export(char **args, t_env *env, t_env *secret)
{
	int		error_ret;
	int		new_env;

<<<<<<< HEAD
	if (!args[1])
		return (print_sorted_env(secret), SUCCESS);
	error_ret = is_valid_env(args[1]);
	if (args[1][0] == '=')
		error_ret = -3;
	if (error_ret <= 0)
		return (print_error(error_ret, args[1]));
	new_env = 0;
	if (error_ret != 2)
		new_env = is_in_env(env, args[1]);
	if (new_env == 0)
	{
		if (error_ret == 1)
			env_add(args[1], env);
		else
			env_add(args[1], secret);
	}
	return (SUCCESS);
}
=======
    if (!env || !secret)
        return (-1);

    new_env = 0;
    if (!args[1])
    {
        print_sorted_env(secret);
        return (SUCCESS);
    }
    else
    {
        printf("Argument provided to export: %s\n", args[1]);
        error_ret = is_valid_env(args[1]);
        if (args[1][0] == '=')
        {
            error_ret = -3;
            printf("Invalid environment variable: starts with '='\n");
        }
        if (error_ret <= 0)
        {
            printf("Invalid environment variable: %s\n", args[1]);
            return (print_error(error_ret, args[1]));
        }
        new_env = error_ret == 2 ? 1 : is_in_env(env, args[1]);
        if (new_env == 0)
        {
            if (error_ret == 1)
            {
                printf("Adding new environment variable to env: %s\n", args[1]);
                env_add(args[1], env);
            }
            else
            {
                printf("Adding new environment variable to secret: %s\n", args[1]);
                env_add(args[1], secret);
            }
        }
    }
    printf("Exiting ft_export\n");
    return (SUCCESS);
}
>>>>>>> origin/check
