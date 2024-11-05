/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:29:08 by nchok             #+#    #+#             */
/*   Updated: 2024/11/05 13:36:12 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../header/minishell.h"

t_lexer *clear_node(t_lexer **lexer)
{
	if ((*lexer)->str)
	{
		free((*lexer)->str);
		(*lexer)->str = NULL;
	}
	free(*lexer);
	*lexer = NULL;
	return (NULL);
}

void	del_first_node(t_lexer **lexer)
{
	t_lexer	*ptr;

	ptr = *lexer;
	if (!ptr)
		return ;
	*lexer = ptr->next;
	clear_node(&ptr);
	if (*lexer)
		(*lexer)->prev = NULL;
}

void	del_one_node(t_lexer **lexer, int i)
{
	t_lexer	*ptr;
	t_lexer	*prev;
	t_lexer *start;

	ptr = *lexer;
	start = *lexer;
	if ((*lexer)->i == i)
	{
		del_first_node(lexer);
		return ;
	}
	while (ptr && ptr->i != i) // transverse to find node with index
	{
		prev = ptr;
		ptr = ptr->next;
	}
	if (prev) // if node is not NULL, found the index
		prev->next = ptr->next;
	else // if node is NULL, found the index && node is last
		prev->next = NULL;
	if (prev->next)
		prev->next->prev = prev; // set the next node's prev to prev
	clear_node(&ptr); // clear the current node
	*lexer = start;
}
