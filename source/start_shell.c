/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 22:32:56 by nchok             #+#    #+#             */
/*   Updated: 2024/11/11 22:32:56 by hheng            ###   ########.fr       */
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




/* Try to combine version -- will cause seg fault,
	due to i used t_token to parse and Nelson use t_lexer to parse*/
int	start_shell(t_general *utils)
{
	t_shell mini;
	t_token *token;
	char *line;

	// Initialize the t_shell structure
	mini.env_vars = utils->env_vars;        // Directly assign env_vars
	mini.hidden_env_vars = utils->env_vars; // Directly assign hidden_env_vars
	mini.skip_execution = 0;
	mini.process_charge = 1;
	mini.pipe_input_fd = -1;
	mini.pipe_output_fd = -1;
	mini.return_code = 0;

	while (1)
	{
		// Display prompt and read input
		line = readline("\033[31m42Minishell-1.0$ \033[0m");
		utils->line = ft_strtrim(line, " "); // trim the spaces in front & back
		free(line); // Free the original line to avoid memory leak
		if (!utils->line) // Check if the line is empty
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			exit(EXIT_SUCCESS);
		}

		if (utils->line[0] == '\0') // Check if the line is empty
			return (clean_utils(utils));
		// Add input to history
		add_history(line);

		// Check for unmatched quotes before proceeding (use closed_quotes or your validation)
		if (closed_quotes(utils->line) == FALSE)
		{
			return (error_message(2, utils));
		}
		utils->mini = &mini;
		// Tokenize the input line (assuming read_token processes into t_lexer)
		if (read_token(utils) == 0)
		{
			return (error_message(1, utils));
		}
		// Now parse the tokens using start_parsing (you may need to adjust based on your lexer structure)
		start_parsing(utils);
			// This will process your lexer and tokens into a command structure
		// print_cmds(utils);
		setup_executor(utils); // #####################


		// Now you can create the command token for execution after parsing
		token = malloc(sizeof(t_token));
		if (!token)
		{
			ft_putendl_fd("Failed to allocate memory for token",
				STDERR_FILENO);
			free(line);
			continue ;
		}

		token->str = utils->line;     // Set the token's string to the input line
		token->type = COMMAND; // Set the token type (e.g., as a command)
		token->next = NULL;

		// Execute the command from the token
		// exec_cmd_from_token(&mini, token);

		// Free allocated memory for token and line
		free(token);
	}
}

void	print_cmds(t_general *utils)
{
	t_cmds *ptr;
	int i;
	int count;

	ptr = utils->cmds;
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

void	print_lexer(t_general *utils)
{
	t_lexer *ptr;

	ptr = utils->lexer_list;
	printf("------printing lexer------\n");
	while (ptr)
	{
		printf("str: %s\n", ptr->str);
		printf("token_type: %d\n", ptr->token_type);
		ptr = ptr->next;
	}
}
