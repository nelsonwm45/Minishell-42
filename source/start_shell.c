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
		if (read_token(utils) == 0)
			return (error_message(1, utils));
		start_parsing(utils);
		print_parser(utils);
		// if (is_builtin(utils->line))
		// 	exec_builtin(&utils->line, (t_shell *)utils);
		if (same_str(utils->line, "exit"))
			return (clean_utils(utils));
	}
}

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
