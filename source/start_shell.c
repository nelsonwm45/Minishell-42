/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:21:28 by nchok             #+#    #+#             */
/*   Updated: 2024/11/20 10:21:28 by nchok            ###   ########.fr       */
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

void	init_shell(t_shell *mini, t_general *utils)
{
	mini->env_vars = utils->env_vars;        // Directly assign env_vars
	mini->hidden_env_vars = utils->env_vars; // Directly assign hidden_env_vars
	mini->skip_execution = 0;
	mini->process_charge = 1;
	mini->pipe_input_fd = -1;
	mini->pipe_output_fd = -1;
	mini->return_code = 0;
}

int	start_shell(t_general *utils)
{
	t_shell mini;
	// t_token *token;
	char *line;

	init_shell(&mini, utils);
	while (1)
	{
		line = readline("\033[31m42Minishell-1.0$ \033[0m");
		utils->line = ft_strtrim(line, " ");
		if (!utils->line)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			exit(EXIT_SUCCESS);
		}
		if (utils->line[0] == '\0')
			return (clean_utils(utils));
		add_history(line);
		free(line);

		if (closed_quotes(utils->line) == FALSE)
		{
			return (error_message(2, utils));
		}
		utils->mini = &mini;
		// Modify signals for child process
		run_signals(2);
		if (read_token(utils) == 0)
		{
			return (error_message(1, utils));
		}
		start_parsing(utils);
		setup_executor(utils);
		// Restore signals for the main process after execution
		run_signals(1);
		clean_utils(utils);

			// token = malloc(sizeof(t_token));
			// if (!token)
			// {
			// 	ft_putendl_fd("Failed to allocate memory for token",
			// 		STDERR_FILENO);
			// 	free(line);
			// 	continue ;
			// }
			
			// token->str = utils->line;
			// token->type = COMMAND;
			// token->next = NULL;

			// free(token);
	}
	return (0);
}

void	print_cmds(t_cmds *cmds)
{
	t_cmds *ptr;
	int i;
	int count;

	ptr = cmds;
	count = 0;
	printf("------printing cmds------\n");
	while (ptr)
	{
		i = 0;
		printf("~~~~>>Node: %d\n", count);
		while (ptr->str[i])
		{
			printf("str: %s\n", ptr->str[i]);
			i++;
		}
		printf("builtin: %d\n", ptr->builtin);
		printf("redir_count: %d\n", ptr->redir_count);
		count++;
		ptr = ptr->next;
	}
}

void	print_lexer(t_lexer *lst)
{
	t_lexer *ptr;

	ptr = lst;
	printf("------printing lexer------\n");
	while (ptr)
	{
		printf("str: %s\n", ptr->str);
		printf("token_type: %d\n", ptr->token_type);
		ptr = ptr->next;
	}
}
