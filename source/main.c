/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 22:33:13 by nchok             #+#    #+#             */
/*   Updated: 2024/11/11 22:33:13 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/*
@brief
- compare both string
@return
- return 1 if exactly same string
- return 0 if not same string
@error handling
- can't compare null string
*/
int	same_str(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i])
	{
		if (s1[i] == s2[i])
			i++;
		else
			return (0);
	}
	if (!s1[i] && !s2[i])
		return (1);
	return (0);
}

static t_env	*create_env_node(char *env_str)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->value = ft_strdup(env_str);
	if (!new_node->value)
	{
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}

t_env	*convert_envp_to_list(char **envp)
{
	t_env	*env_list;
	t_env	*new_node;
	t_env	*current;
	char	**env;

	env_list = NULL;
	env = envp;
	while (*env)
	{
		new_node = create_env_node(*env);
		if (!new_node)
			return (NULL);
		if (!env_list)
			env_list = new_node;
		else
		{
			current = env_list;
			while (current->next)
				current = current->next;
			current->next = new_node;
		}
		env++;
	}
	return (env_list);
}

void	cleanup_before_exit(t_general *utils)
{
	if (utils->line)
		free(utils->line);
	if (utils->envp)
		free_array(utils->envp);
	if (utils->path)
		free_array(utils->path);
	if (utils->pwd)
		free(utils->pwd);
	if (utils->oldpwd)
		free(utils->oldpwd);
	if (utils->pid)
		free(utils->pid);
}

int	main(int ac, char **av, char **envp)
{
	t_general	utils;
	t_shell		mini;

	if (ac != 1 || av[1] != NULL)
	{
		ft_putendl_fd("Program does not accept arguments", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	process_envp(envp, &utils);
	utils.exit_status = 0;
	utils.env_vars = convert_envp_to_list(envp);
	init_shell(&mini, &utils);
	run_signals(1);
	start_shell(&utils);
	cleanup_before_exit(&utils);
	return (g_ret_number);
}
