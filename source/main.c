/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:51:36 by nchok             #+#    #+#             */
/*   Updated: 2024/08/29 16:43:37 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/*
	@brief
	- compare both string
	@return
	- return 1 if exactly same string
	- return 0 if not same string
	@error handling
	- can't compare null string
*/
int		same_str(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i])
	{
		if (s1[i] == s2[i])
			i++;
		else
			return (0);
	}
	if (!s1[i] && !s2[i])
		return (1);
	else
		return (0);
}

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
	char	*line;

	(void)ac;
	(void)av;
	(void)env;
	print_welcome();
	while (1)
	{
		line = readline("42Minishell-1.0$ ");
		if (*line)
			add_history(line);
		if (same_str(line, "exit") == 1)
			exit(EXIT_SUCCESS);
	}
	return (0);
}
