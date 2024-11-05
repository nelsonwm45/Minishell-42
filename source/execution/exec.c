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

void	exec_cmd(t_shell *mini, t_token *token)
{
	char	**cmd;
	int		i;

	if (mini->process_charge == 0)
		return ;
	cmd = cmd_tab(token);
	i = 0;
	while (cmd && cmd[i])
	{
		cmd[i] = expansions(cmd[i], mini->env_vars, mini->return_code);
		i++;
	}
	if (cmd && ft_strcmp(cmd[0], "exit") == 0 && has_pipe(token) == 0)
		mini_exit(mini, cmd);
	else if (cmd && is_builtin(cmd[0]))
		mini->return_code = exec_builtin(cmd, mini);
	else if (cmd)
		mini->return_code = exec_bin(cmd, mini->env_vars, mini);
	free_tab(cmd);
	ft_close(mini->pipe_input_fd);
	ft_close(mini->pipe_output_fd);
	mini->pipe_input_fd = -1;
	mini->pipe_output_fd = -1;
	mini->process_charge = 0;
}