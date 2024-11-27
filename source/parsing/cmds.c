/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:47:46 by nchok             #+#    #+#             */
/*   Updated: 2024/11/26 16:54:44 by nchok            ###   ########.fr       */
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
	while (size > 0 && ptr->token_type != PIPE)
	{
		if (ptr->str != NULL)
		{
			str[i] = ft_strdup(ptr->str);
			i++;
		}
		del_one_node(&parser->lexer_list, ptr->i);
		ptr = parser->lexer_list;
		size--;
	}
	str[i] = NULL;
	return (str);
}

t_cmds	*init_cmds(t_parser *parser)
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
