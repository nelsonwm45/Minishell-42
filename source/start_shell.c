/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:38:48 by nchok             #+#    #+#             */
/*   Updated: 2024/11/07 11:38:48 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"


int	find_next_quote(char *line, int *i, int *num_quote, char quote){
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

// t_env *convert_envp_to_list(char **envp)
// {
//     t_env *env_list = NULL;
//     t_env *new_node;
//     t_env *current;
//     char **env;

//     for (env = envp; *env != NULL; env++)
//     {
//         new_node = malloc(sizeof(t_env));
//         if (!new_node)
//         {
//             perror("malloc");
//             return NULL;
//         }
//         new_node->var = strdup(*env);
//         if (!new_node->var)
//         {
//             perror("strdup");
//             free(new_node);
//             return NULL;
//         }
//         new_node->next = NULL;

//         if (!env_list)
//         {
//             env_list = new_node;
//         }
//         else
//         {
//             current = env_list;
//             while (current->next)
//                 current = current->next;
//             current->next = new_node;
//         }
//     }
//     return env_list;
// }


/* Original version*/


// int	start_shell(t_general *utils)
// {
// 	char *line;

// 	while (1)
// 	{
// 		line = readline("42Minishell-1.0$ ");
// 		utils->line = ft_strtrim(line, " "); // trim the spaces in front & back
// 		free(line);// Free the original line to avoid memory leak
// 		if (!utils->line)
// 		{
// 			ft_putendl_fd("exit", STDOUT_FILENO);
// 			exit(EXIT_SUCCESS);
// 		}
// 		if (utils->line[0] == '\0')
// 			return (clean_utils(utils));
// 		add_history(utils->line);
// 		if (closed_quotes(utils->line) == FALSE)
// 			return (error_message(2, utils));
// 		if (read_token(utils) == 0)
// 			return (error_message(1, utils));
// 		start_parsing(utils);
// 		print_parser(utils);
// 		// if (is_builtin(utils->line))
// 		// 	exec_builtin(&utils->line, (t_shell *)utils);
// 		if (same_str(utils->line, "exit"))
// 			return (clean_utils(utils));
// 	}
// }

/* Winnie version*/
void start_shell(t_general *utils)
{
    t_shell mini;
    t_token *token;
    char *line;

    // Initialize the t_shell structure
    mini.env_vars = utils->env_vars; // Directly assign env_vars
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


/* Try to combine version -- will cause seg fault, due to i used t_token to parse and Nelson use t_lexer to parse*/
// void start_shell(t_general *utils)
// {
//     t_shell mini;
//     t_token *token;
//     // t_lexer *lexer;  // Assuming you need a lexer for parsing
//     char *line;

//     // Initialize the t_shell structure
//     mini.env_vars = utils->env_vars; // Directly assign env_vars
//     mini.hidden_env_vars = utils->env_vars; // Directly assign hidden_env_vars
//     mini.skip_execution = 0;
//     mini.process_charge = 1;
//     mini.pipe_input_fd = -1;
//     mini.pipe_output_fd = -1;
//     mini.return_code = 0;

//     while (1)
//     {
//         // Display prompt and read input
//         line = readline("\033[31m42Minishell-1.0$ \033[0m");
//         if (!line)
//             break;

//         // Add input to history
//         add_history(line);

//         // Check for unmatched quotes before proceeding (use closed_quotes or your validation)
//         if (closed_quotes(line) == FALSE)
//         {
//             error_message(2, utils);
//             free(line);
//             continue;
//         }

//         // Tokenize the input line (assuming read_token processes into t_lexer)
//         if (read_token(utils) == 0)
//         {
//             error_message(1, utils);
//             free(line);
//             continue;
//         }

//         // Now parse the tokens using start_parsing (you may need to adjust based on your lexer structure)
//         start_parsing(utils);  // This will process your lexer and tokens into a command structure

//         // Print or debug the parsed structure if needed
//         print_parser(utils);   // This prints or debugs the parsed structure

//         // Now you can create the command token for execution after parsing
//         token = malloc(sizeof(t_token));
//         if (!token)
//         {
//             ft_putendl_fd("Failed to allocate memory for token", STDERR_FILENO);
//             free(line);
//             continue;
//         }

//         token->str = line;       // Set the token's string to the input line
//         token->type = COMMAND;   // Set the token type (e.g., as a command)
//         token->next = NULL;

//         // Execute the command from the token
//         exec_cmd_from_token(&mini, token);

//         // Free allocated memory for token and line
//         free(token);
//         free(line);
//     }
// }






void	print_parser(t_general *utils)
{
	t_cmds	*ptr;
	int		i;

	i = 0;
	ptr = utils->cmds;
	while (ptr)
	{
		printf("str: %s\n", ptr->str[i]);
		printf("redir_count: %d\n", ptr->redir_count);
		i++;
		ptr = ptr->next;
	}
}
