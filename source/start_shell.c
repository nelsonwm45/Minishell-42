/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: nchok <nchok@student.42kl.edu.my>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/10/15 17:15:41 by nchok             #+#    #+#             */
/*   Updated: 2024/10/28 16:05:13 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"


int	find_next_quote(char *line, int *i, int *num_quote, char quote)
{
	int j;

	j = *i + 1; // go to next cha after the quote
	while (line[j])
	{
		if (line[j] == quote)
		{
			(*num_quote)++;
			break ;
		}
		j++;
	}
	*i = j;
	return (0);
}

int	closed_quotes(char *line)
{
	int i;
	int sing_q;
	int doub_q;

	i = 0;
	sing_q = 0;
	doub_q = 0;
	while (line[i])
	{
		if (line[i] == '\'') // increase the single quote count
		{
			sing_q++;
			find_next_quote(line, &i, &sing_q, '\'');
				// find the next single quote
		}
		if (line[i] == '\"') // increase the double quote count
		{
			doub_q++;
			find_next_quote(line, &i, &doub_q, '\"');
		}
		i++;
	}
	if (sing_q % 2 == 1 || doub_q % 2 == 1)
		return (FALSE);
	return (TRUE);
}

void start_shell(t_general *utils)
{
    t_shell mini;
    t_token *token;
    char *line;

    // Initialize the t_shell structure
    mini.env_vars = utils->env_vars;
    mini.hidden_env_vars = NULL;
    mini.skip_execution = 0;
    mini.process_charge = 1;
    mini.pipe_input_fd = -1;
    mini.pipe_output_fd = -1;
    mini.return_code = 0;

    while (1)
    {
        // Display prompt and read input
        line = readline("\033[31m""42Minishell-1.0$ ""\033[0m");
        if (!line)
            break;

        // Add input to history
        add_history(line);

        // Create a token from the input line
        token = malloc(sizeof(t_token));
        if (!token)
        {
            ft_putendl_fd("Failed to allocate memory for token", STDERR_FILENO);
            free(line);
            continue;
        }
        token->str = line;
        token->type = COMMAND; // Set the token type
        token->next = NULL;

        // Execute the command from the token
        exec_cmd_from_token(&mini, token);

        // Free allocated memory for token and line
        free(token);
        free(line);
	}
}

// void	print_parser(t_general *utils)
// {
// 	t_cmds	*ptr;
// 	int		i;

// 	i = 0;
// 	ptr = utils->cmds;
// 	while (ptr)
// 	{
// 		printf("str: %s\n", ptr->str[i]);
// 		printf("redir_count: %d\n", ptr->redir_count);
// 		i++;
// 		ptr = ptr->next;
// 	}
// }
