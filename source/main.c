/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
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
int		same_str(char *s1, char *s2)
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
	else
		return (0);
}

t_env *convert_envp_to_list(char **envp) {
    t_env *head = NULL;
    t_env *current = NULL;
    t_env *new_node = NULL;
    int i = 0;

    while (envp[i]) {
        new_node = malloc(sizeof(t_env));
        if (!new_node)
            return NULL; // Handle allocation failure
        new_node->value = ft_strdup(envp[i]);
        new_node->next = NULL;
        if (!head)
            head = new_node;
        else
            current->next = new_node;
        current = new_node;
        i++;
    }
    return head;
}

int main(int ac, char **av, char **envp)
{
    t_general utils;
    t_shell mini;
    t_token *token;

    if (ac != 1 || av[1] != NULL)
    {
        ft_putendl_fd("Program does not accept arguments", STDERR_FILENO);
        exit(EXIT_FAILURE);
    }

    // Initialize utils and process environment variables
    process_envp(envp, &utils);

    // Convert envp to t_env linked list
    mini.env_vars = convert_envp_to_list(envp);
    mini.hidden_env_vars = NULL; // Initialize other members as needed

    // Create or obtain a token (this is just an example, adjust as needed)
    token = malloc(sizeof(t_token));
    if (!token)
    {
        ft_putendl_fd("Failed to allocate memory for token", STDERR_FILENO);
        exit(EXIT_FAILURE);
    }
    token->str = "example_command"; // Set the command string
    token->type = COMMAND; // Set the token type
    token->next = NULL; // Set the next token if any

    // Call exec_cmd function
    exec_cmd(&mini, token);

    // Free allocated memory for token
    free(token);

    // Start the shell
    start_shell(&utils);

    return (0);
}