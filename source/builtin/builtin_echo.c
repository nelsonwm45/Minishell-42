/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:44:45 by hheng             #+#    #+#             */
/*   Updated: 2024/11/29 04:14:39 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Counts the number of arguments in the array.
 * 
 * @param args (Array) of arguments.
 * @return The number of arguments.
 */

static	int	nb_args(char **args)
{
	int		size;

	size = 0;
	while (args[size])
		size++;
	return (size);
}

// n_option = 0 , -n flag not been encountered
// n_option = 1 , -n flag found
int	ft_echo(char **args)
{
	int		i;
	int		n_option;

	i = 1;
	n_option = 0;
	if (nb_args(args) > 1)
	{
		while (args[i] && ft_strcmp(args[i], "-n") == 0)
		{
			n_option = 1;
			i++;
		}
		while (args[i])
		{
			ft_putstr_fd(args[i], 1);
			if (args[i + 1] && args[i][0] != '\0')
				write(1, " ", 1);
			i++;
		}
	}
	if (n_option == 0)
		write(1, "\n", 1);
	return (SUCCESS);
}
