/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:29:08 by nchok             #+#    #+#             */
/*   Updated: 2024/11/26 16:54:13 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_lexer	*clear_node(t_lexer **lexer)
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

/*
	@brief
	- delete the first node in the lexer list

*/
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

/*
	@brief
	- delete a node in the lexer list with the given index

	Check if the first node has the target index
	Delete the first node directly
	Traverse the list to find the node with the given index
		save previous node
		move to the next node
	If the node was not found, ptr will be NULL, so return
	Adjust the pointers to bypass the node to delete
	Free the current node
*/
void	del_one_node(t_lexer **lexer, int i)
{
	t_lexer	*ptr;
	t_lexer	*prev;

	prev = NULL;
	ptr = *lexer;
	if (ptr && ptr->i == i)
	{
		del_first_node(lexer);
		return ;
	}
	while (ptr && ptr->i != i)
	{
		prev = ptr;
		ptr = ptr->next;
	}
	if (!ptr)
		return ;
	if (prev)
		prev->next = ptr->next;
	if (ptr->next)
		ptr->next->prev = prev;
	clear_node(&ptr);
}
