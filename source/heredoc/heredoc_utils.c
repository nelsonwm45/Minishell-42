/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 02:20:36 by nchok             #+#    #+#             */
/*   Updated: 2024/11/22 02:21:02 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../header/minishell.h"

void	print_redir(t_lexer *ptr)
{
	while (ptr)
	{
		printf("ptr->str: %s\n", ptr->str);
		ptr = ptr->next;
	}
}