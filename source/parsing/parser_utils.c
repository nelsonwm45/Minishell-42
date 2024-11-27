/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:27:48 by nchok             #+#    #+#             */
/*   Updated: 2024/11/26 16:56:02 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_type	scan_double_token(t_lexer *lexer)
{
	t_lexer	*ptr;
	t_type	token;

	ptr = lexer;
	if (pipe_first(ptr) == PIPE)
		return (PIPE);
	while (ptr->next)
	{
		token = ptr->next->token_type;
		if (ptr->token_type == SMALLSMALL && token != 0)
			return (token);
		if (ptr->token_type == BIGBIG && token != 0)
			return (token);
		if (ptr->token_type == BIG && token != 0)
			return (token);
		if (ptr->token_type == SMALL && token != 0)
			return (token);
		if (ptr->token_type == PIPE && token != 0)
			return (PIPE);
		ptr = ptr->next;
	}
	return (0);
}

int	pipe_first(t_lexer *lexer)
{
	if (lexer->token_type == PIPE)
		return (PIPE);
	return (0);
}
