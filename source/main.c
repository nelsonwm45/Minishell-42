/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: hheng <hheng@student.42kl.edu.my>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/08/27 13:51:36 by nchok             #+#    #+#             */
/*   Updated: 2024/10/28 16:16:27 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
	int i;

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
	else
		return (0);
}

t_env	*convert_envp_to_list(char **envp)
{
	t_env *env_list = NULL;
	t_env *new_node;
	t_env *current;
	char **env;

	for (env = envp; *env != NULL; env++)
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
		{
			perror("malloc");
			return (NULL);
		}
		new_node->value = strdup(*env);
		if (!new_node->value)
		{
			perror("strdup");
			free(new_node);
			return (NULL);
		}
		new_node->next = NULL;

		if (!env_list)
		{
			env_list = new_node;
		}
		else
		{
			current = env_list;
			while (current->next)
				current = current->next;
			current->next = new_node;
		}
	}
	return (env_list);
}

void	exec_cmd_from_token(t_shell *mini, t_token *token)
{
	char **args = ft_split(token->str, ' ');
		// Split the token string into arguments

	if (is_builtin(args[0])) // Check if the command is built-in
	{
		exec_builtin(args, mini); // Execute the built-in command
	}
	else
	{
		// Call the existing exec_cmd to handle external commands
		exec_cmd(mini, token);
	}

	// Free allocated memory for args (important to avoid memory leaks)
	free(args);
}

int	main(int ac, char **av, char **envp)
{
	t_general utils;

	if (ac != 1 || av[1] != NULL)
	{
		ft_putendl_fd("Program does not accept arguments", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}

	utils.env_vars = convert_envp_to_list(envp);

	start_shell(&utils);

	return (0);
}