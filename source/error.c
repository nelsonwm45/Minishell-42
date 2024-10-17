/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:54:36 by nchok             #+#    #+#             */
/*   Updated: 2024/10/16 17:05:54 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../header/minishell.h"

int	clean_utils(t_env *utils)
{
	int	i;

	i = 0;
	while (utils->envp[i] != NULL)
	{
		free(utils->envp[i]);
		i++;
	}
	free(utils->envp);
	free(utils->path);
	free(utils->pwd);
	free(utils->oldpwd);
	free(utils->line);
	return (0);
}

int	error_message(int error_code, t_env *utils)
{
	if (error_code == 1)
		ft_putstr_fd("Syntax error near unexpected token 'newline'\n", STDERR_FILENO);
	else if (error_code == 2)
		ft_putstr_fd("Syntax error: unable to locate closing quote\n", STDERR_FILENO);
	clean_utils(utils);
	return (EXIT_FAILURE);
}