/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:45:21 by hheng             #+#    #+#             */
/*   Updated: 2024/10/30 13:45:21 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	env_size(char *env)
{
	size_t		i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

static void		free_node(t_shell *mini, t_env *env)
{
	if (mini->env_vars == env && env->next == NULL)
	{
		ft_memdel(mini->env_vars->value);
		mini->env_vars->value = NULL;
		mini->env_vars->next = NULL;
		return ;
	}
	ft_memdel(env->value);
	ft_memdel(env);
}

int				ft_unset(char **a, t_shell *mini)
{
	t_env	*env;
	t_env	*tmp;

	env = mini->env_vars;
	if (!(a[1]))
		return (SUCCESS);
	if (ft_strncmp(a[1], env->value, env_size(env->value)) == 0)
	{
		mini->env_vars = (env->next) ? env->next : mini->env_vars;
		free_node(mini, env);
		return (SUCCESS);
	}
	while (env && env->next)
	{
		if (ft_strncmp(a[1], env->next->value, env_size(env->next->value)) == 0)
		{
			tmp = env->next->next;
			free_node(mini, env->next);
			env->next = tmp;
			return (SUCCESS);
		}
		env = env->next;
	}
	return (SUCCESS);
}