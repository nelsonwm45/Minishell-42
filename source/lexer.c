/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:48:51 by nchok             #+#    #+#             */
/*   Updated: 2024/10/28 15:38:23 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../header/minishell.h"

t_lexer	*create_node(char *str, t_token token_type)
{
	t_lexer	*node;
	static int	i = 0;

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

void	add_to_backlexerr(t_lexer *new, t_lexer **lexer_list)
{
	t_lexer	*ptr;
	
	ptr = *lexer_list;
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = new;
}