/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:54:36 by nchok             #+#    #+#             */
/*   Updated: 2024/10/28 15:42:37 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../header/minishell.h"
/*
	@brief
	- free the array
*/
void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	clean_utils(t_general *utils)
{
	free_array(utils->envp);
	free_array(utils->path);
	free(utils->pwd);
	free(utils->oldpwd);
	free(utils->line);
	return (0);
}

int	error_message(int error_code, t_general *utils)
{
	if (error_code == 1)
		ft_putstr_fd("Syntax error near unexpected token 'newline'\n", STDERR_FILENO);
	else if (error_code == 2)
		ft_putstr_fd("Syntax error: unable to locate closing quote\n", STDERR_FILENO);
	clean_utils(utils);
	return (EXIT_FAILURE);
}