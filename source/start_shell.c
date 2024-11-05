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

int	start_shell(t_general *utils)
{
	char *line;

	while (1)
	{
		line = readline("42Minishell-1.0$ ");
		utils->line = ft_strtrim(line, " "); // trim the spaces in front & back
		free(line);// Free the original line to avoid memory leak
		if (!utils->line)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			exit(EXIT_SUCCESS);
		}
		if (utils->line[0] == '\0')
			return (clean_utils(utils));
		add_history(utils->line);
		if (closed_quotes(utils->line) == FALSE)
			return (error_message(2, utils));
		printf("Going In read_token\n");
		if (read_token(utils) == 0)
			return (error_message(1, utils));
		start_parsing(utils);
		if (is_builtin(utils->line))
			exec_builtin(&utils->line, (t_shell *)utils);
		if (same_str(utils->line, "exit"))
			return (clean_utils(utils));
	}
}