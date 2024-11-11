/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:29:08 by nchok             #+#    #+#             */
/*   Updated: 2024/11/11 11:17:15 by nchok            ###   ########.fr       */
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

/*
	@brief
	- delete the first node in the lexer list
	
*/
void	del_first_node(t_lexer **lexer)
{
	t_lexer	*ptr;

	ptr = *lexer;
	if (!ptr)
		return;
	*lexer = ptr->next; // Update lexer to point to the second node
	clear_node(&ptr);    // Clear the first node
	// Set the new first node's prev pointer to NULL if it exists
	if (*lexer)
		(*lexer)->prev = NULL;
}

void	del_one_node(t_lexer **lexer, int i)
{
	t_lexer	*ptr;
	t_lexer	*prev = NULL;

	ptr = *lexer;
	// Check if the first node has the target index
	if (ptr && ptr->i == i)
	{
		del_first_node(lexer); // Delete the first node directly
		return;
	}
	// Traverse the list to find the node with the given index
	while (ptr && ptr->i != i)
	{
		prev = ptr;      // Save the previous node
		ptr = ptr->next; // Move to the next node
	}
	// If the node was not found, ptr will be NULL, so return
	if (!ptr)
		return;
	// Adjust the pointers to bypass the node to delete
	if (prev)
		prev->next = ptr->next;
	// If there's a next node, update its prev pointer
	if (ptr->next)
		ptr->next->prev = prev;
	clear_node(&ptr); // Free the current node
}

