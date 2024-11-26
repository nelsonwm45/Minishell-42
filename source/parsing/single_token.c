/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:20:23 by nchok             #+#    #+#             */
/*   Updated: 2024/11/26 17:03:43 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	first_single_token(t_lexer *lexer)
{
	t_lexer	*ptr;
	t_type	token_type;

	ptr = lexer;
	token_type = scan_first_token(ptr);
	if (token_type == 0)
		return (EXIT_SUCCESS);
	if (token_type == PIPE)
	{
		double_token_error(ptr, token_type);
		return (EXIT_FAILURE);
	}
	else if (token_type == BIG || token_type == SMALL
		|| token_type == SMALLSMALL || token_type == BIGBIG)
	{
		error_message(1, NULL);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

t_type	scan_first_token(t_lexer *lexer)
{
	t_lexer	*ptr;
	t_type	token_type;

	ptr = lexer;
	if (ptr && ptr->next == NULL)
	{
		token_type = ptr->token_type;
		if (token_type == BIG || token_type == SMALL || token_type == SMALLSMALL
			|| token_type == BIGBIG)
			return (token_type);
		if (token_type == PIPE)
			return (PIPE);
	}
	return (0);
}
