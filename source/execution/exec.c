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
    int i = 0;

    if (mini->process_charge == 0)
        return;

    cmd = cmd_tab(token);
     if (!cmd) {
        fprintf(stderr, "Error: cmd_tab returned NULL in exec_cmd.\n");
        return;
    }
    if (cmd == NULL || cmd[0] == NULL) // Ensure cmd is not NULL and has content
    {
        free_tab(cmd); // Clean up if cmd is empty or invalid
        return;
    }

    // Expand each part of the command if cmd is not empty
    while (cmd[i])
    {
          if (!cmd[i]) {
            fprintf(stderr, "Warning: Uninitialized command argument at index %d.\n", i);
            break;
        }

        cmd[i] = expansions(cmd[i], mini->env_vars, mini->return_code);
        i++;
    }

    // Check if command is "exit" without pipes, then exit
   if (cmd[0] && ft_strcmp(cmd[0], "exit") == 0 && has_pipe(token) == 0)
    {
        mini_exit(mini, cmd);
    }
    else if (cmd[0] && is_builtin(cmd[0])) // Execute builtin if it's a recognized command
    {
        mini->return_code = exec_builtin(cmd, mini);
    }
    else if (cmd[0])// Otherwise, execute as external command
    {
        mini->return_code = exec_bin(cmd, mini->env_vars, mini);
    }

    free_tab(cmd); // Free the command array

    // Close file descriptors if valid
    // if (mini->pipe_input_fd != -1)
    //     ft_close(mini->pipe_input_fd);
    // if (mini->pipe_output_fd != -1)
    //     ft_close(mini->pipe_output_fd);
    ft_close(mini->pipe_input_fd);
    ft_close(mini->pipe_output_fd);

    // Reset mini struct states
    mini->pipe_input_fd = -1;
    mini->pipe_output_fd = -1;
    mini->process_charge = 0;
}
