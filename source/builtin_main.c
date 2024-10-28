/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: hheng <hheng@student.42kl.edu.my>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/09/08 13:22:48 by hheng             #+#    #+#             */
/*   Updated: 2024/09/08 13:22:48 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"


// Function to split the input line into arguments using spaces as delimiters
void	parse_command(char *line, char **args)
{
	int i = 0;
	char *token = line;

	while (*token != '\0')
	{
		// Skip over any leading spaces
		while (*token == ' ')
		{
			token++;
		}
		if (*token == '\0')
		{
			break ;
		}

		// Add the token to the args array
		args[i++] = token;

		// Find the end of the current token (space or null terminator)
		while (*token != '\0' && *token != ' ')
		{
			token++;
		}

		// If a space was found, null-terminate the token and move to the next
		if (*token != '\0')
		{
			*token = '\0';
			token++;
		}
	}
	args[i] = NULL; // Null-terminate the args array
}

// Main shell loop function
void	shell_loop(void)
{
	char *line;
	char *args[64];
	int status = 1;

	while (status)
	{
		// Use readline to get input
		line = readline("> ");
		if (line == NULL)
		{
			// Handle EOF or read error
			printf("\n");
			break ;
		}

		// Add the input to history
		if (*line)
		{
			add_history(line);
		}

		// Parse the command into arguments
		parse_command(line, args);

		// Execute the command if args[0] is not empty
		if (args[0] != NULL)
		{
			status = execute_command(args);
		}

		// Free the line after use
		free(line);
	}
}

// Main function
int	main(void)
{
	shell_loop();
	rl_clear_history(); // Clear the history at the end
	return (0);
}