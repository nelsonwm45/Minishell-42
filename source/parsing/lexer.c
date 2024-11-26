/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:55:12 by nchok             #+#    #+#             */
/*   Updated: 2024/11/26 16:55:12 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_lexer	*create_node(char *str, t_type token_type)
{
	t_lexer		*node;
	static int	i = 0;

	node = ft_calloc(1, sizeof(t_lexer));
	if (!node)
		return (NULL);
	if (str)
		node->str = str;
	else
		node->str = NULL;
	if (token_type)
		node->token_type = token_type;
	else
		node->token_type = 0;
	node->i = i++;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

int	add_to_backlexer(t_lexer *new, t_lexer **lexer_list)
{
	t_lexer	*ptr;

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
