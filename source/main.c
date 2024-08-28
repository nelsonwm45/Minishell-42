/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:51:36 by nchok             #+#    #+#             */
/*   Updated: 2024/08/28 16:11:15 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	print_welcome(void)
{
	int	i;

	i = 0;
	while (i <= 12)
	{
		if (welcome[i] !=  NULL)
			printf("%s%s\n", COLOR_RED, welcome[i++]);
		if (welcome[i] !=  NULL)
			printf("%s%s\n", COLOR_GREEN, welcome[i++]);
		if (welcome[i] !=  NULL)
			printf("%s%s\n", COLOR_YELLOW, welcome[i++]);
		if (welcome[i] !=  NULL)
			printf("%s%s\n", COLOR_BLUE, welcome[i++]);
		if (welcome[i] !=  NULL)
			printf("%s%s\n", COLOR_MAGENTA, welcome[i++]);
	}
	printf("%s\n", COLOR_RESET);
}

int main(int ac, char **av, char **env)
{
	char *line;

	(void)ac;
	(void)av;
	(void)env;
	print_welcome();
	while (1)
	{
		printf("%s42Minishell >", COLOR_GREEN);
		line = readline(STDIN_FILENO);
	}
	return (0);
}
