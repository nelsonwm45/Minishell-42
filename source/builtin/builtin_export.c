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

int env_add(const char *value, t_env *env)
{
    t_env *new;
    t_env *tmp;

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
}

char		*get_env_name(char *dest, const char *src)
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

int is_in_env(t_env *env, char *args)
{
    char var_name[BUFF_SIZE];
    char env_name[BUFF_SIZE];
    t_env *ptr;

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
}

int ft_export(char **args, t_env *env, t_env *secret)
{
    int new_env;
    int error_ret;

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