/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:47:46 by nchok             #+#    #+#             */
/*   Updated: 2024/11/12 10:54:17 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/*
	@brief
	- count the number of tokens that are not pipes
*/
int	count_no_pipe(t_lexer *lexer_list)
{
	t_lexer	*ptr;
	int		size;

	ptr = lexer_list;
	size = 0;
	while (ptr)
	{
		if (ptr->token_type != PIPE && ptr->i >= 0)
			size++;
		ptr = ptr->next;
	}
	return (size);
}

/*
	@brief
	- convert the str in lexer list to array of strings
*/
char	**form_str(char **str, int size, t_parser *parser)
{
	int		i;
	t_lexer	*ptr;

	ptr = parser->lexer_list;
	i = 0;
	while (ptr && size > 0)
	{
		if (ptr->token_type != PIPE && ptr->str != NULL)
		{
			str[i] = ft_strdup(ptr->str);  // Copy string only if not a pipe
			i++;
		}
		del_one_node(&parser->lexer_list, ptr->i); // Remove the current node after processing
		ptr = parser->lexer_list; // Update ptr to the new head of the list
		size--;
	}
	str[i] = NULL; // Null-terminate the array
	return (str);
}

t_cmds	*init_cmds(t_parser	*parser)
{
	char	**str;
	int		size;
	t_cmds	*cmds;

	recog_redirections(parser);
	size = count_no_pipe(parser->lexer_list);
	str = ft_calloc(size + 1, sizeof(char *));
	while (!str)
		parsing_error(1, parser->utils, parser->lexer_list);
	str = form_str(str, size, parser);
	cmds = create_cmds(str, parser->redirections, parser->redirections_count);
	return (cmds);
}