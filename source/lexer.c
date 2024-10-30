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


#include "../header/minishell.h"

t_lexer	*create_node(char *str, t_type token_type)
{
	t_lexer *node;

	node = ft_calloc(1, sizeof(t_lexer));
	if (!node)
		return (NULL);
	node->str = str;
	node->token_type = token_type;
	node->i = -1;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

int	add_to_backlexer(t_lexer *new, t_lexer **lexer_list)
{
	t_lexer *ptr;

	ptr = *lexer_list;
	if (ptr == NULL) // if the list is empty
	{
		*lexer_list = new;
		if (ptr->i == -1) // assign the index for first node
			ptr->i = 0;
		return (0);
	}
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
		if (ptr->i == -1) // assign the index for the next node
			ptr->i = ptr->prev->i + 1;
	}
	ptr->next = new;
	new->prev = ptr;
	return (0);
}
