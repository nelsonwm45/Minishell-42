/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:10:40 by nchok             #+#    #+#             */
/*   Updated: 2024/11/05 11:11:15 by nchok            ###   ########.fr       */
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
	free(utils->line);
	return (0);
}

int	clean_lexer(t_lexer **lexer)
{
	t_lexer	*ptr;

	ptr = *lexer;
	if (!ptr)
		return (0);
	while (ptr)
	{
		*lexer = ptr->next;
		free(ptr->str);
		free(ptr);
		ptr = *lexer;
	}
	*lexer = NULL;
}