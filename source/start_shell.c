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

int	ft_readline(t_general *utils)
{
	char	*line;
	int		ret;

	ret = EXIT_SUCCESS;
	line = readline("\033[31m42Minishell-1.0$ \033[0m");
	utils->line = ft_strtrim(line, " ");
	if (!utils->line)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	if (utils->line[0] == '\0')
		ret = EXIT_FAILURE;
	add_history(line);
	free(line);
	return (ret);
}

void	init_shell(t_shell *mini, t_general *utils)
{
	mini->env_vars = utils->env_vars;
	mini->hidden_env_vars = utils->env_vars;
	mini->skip_execution = 0;
	mini->process_charge = 1;
	mini->pipe_input_fd = -1;
	mini->pipe_output_fd = -1;
	mini->return_code = 0;
	utils->mini = mini;
}

void	process_token(t_general *utils, int *ret)
{
	if (read_token(utils) == 0)
			*ret = error_message(1, utils);
	if (first_single_token(utils->lexer_list) == EXIT_FAILURE)
			*ret = EXIT_FAILURE;
}

int	start_shell(t_general *utils)
{
	int ret;

	ret = EXIT_SUCCESS;
	while (1)
	{
		ret = ft_readline(utils);
		if (ret != EXIT_FAILURE)
		{
			if (closed_quotes(utils->line) == FALSE)
				ret = error_message(2, utils);
		}
		if (ret != EXIT_FAILURE)
			process_token(utils, &ret);	
		run_signals(2);
		if (ret != EXIT_FAILURE)
			ret = start_parsing(utils);
		if (ret != EXIT_FAILURE)
			ret = setup_executor(utils);
		run_signals(1);
		clean_utils(utils);
		ret = EXIT_SUCCESS;
	}
	return (0);
}
