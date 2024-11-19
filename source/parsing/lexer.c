/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:45:55 by nchok             #+#    #+#             */
/*   Updated: 2024/10/30 14:45:55 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_lexer	*create_node(char *str, t_type token_type)
{
	t_lexer *node;
	static int i = 0;

	node = ft_calloc(1, sizeof(t_lexer));
	if (!node)
		return (NULL);
	node->str = str;
	node->token_type = token_type;
	node->i = i++;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

/*
	High chance segfault due to access to unexisted lexer_list
*/
int	add_to_backlexer(t_lexer *new, t_lexer **lexer_list)
{
	t_lexer *ptr;

	if (*lexer_list == NULL)
	{
		*lexer_list = new;
		return (0);
	}
	ptr = *lexer_list;
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = new;
	new->prev = ptr; 
	return (0);
}
