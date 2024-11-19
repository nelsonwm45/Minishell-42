/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:00:48 by hheng             #+#    #+#             */
/*   Updated: 2024/11/05 14:00:48 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//convert linked list of tokens into array
bool is_end_of_command(t_token *token) {
   
    return (token->type == END_TOKEN); // Replace with the appropriate type
}

char **cmd_tab(t_token *start) {
    t_token *token;
    char **tab;
    int i;

    if (!start)
        return (NULL);

    token = start->next;
    i = 2;

    // Count tokens until end condition
    while (token && !is_end_of_command(token)) {
        token = token->next;
        i++;
    }

    if (!(tab = malloc(sizeof(char *) * i)))
        return (NULL);

    token = start->next;
    tab[0] = start->str;
    i = 1;

    // Fill tab until end condition
    while (token && !is_end_of_command(token)) {
        tab[i++] = token->str;
        token = token->next;
    }

    tab[i] = NULL;
    return (tab);
}

void exec_cmd(t_shell *mini, t_token *token)
{
    char **cmd = NULL;

    if (mini->process_charge == 0) // Check if there's a process to execute.
        return;

    cmd = cmd_tab(token); // Convert the tokenized input into a command array.
    if (!cmd || !cmd[0])  // Ensure the command array and first command are valid.
    {
        free_tab(cmd);    // Clean up and return if invalid.
        return;
    }

    // Check if the command is "exit" and handle it.
    if (ft_strcmp(cmd[0], "exit") == 0)
    {
        ft_exit(mini, cmd); // Exit the shell.
    }
    else if (is_builtin(cmd[0])) // Check if the command is a recognized built-in command.
    {
        mini->return_code = exec_builtin(cmd, mini); // Execute the built-in command.
    }

    free_tab(cmd); // Free the command array.
}
