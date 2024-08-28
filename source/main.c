/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:51:36 by nchok             #+#    #+#             */
/*   Updated: 2024/08/28 14:30:08 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int main(int ac, char **av, char **env)
{
	char *line;

	(void)ac;
	(void)av;
	(void)env;
	while (1)
	{
		printf("42Minishell >");
		line = readline(STDIN_FILENO);
	}
	return (0);
}
