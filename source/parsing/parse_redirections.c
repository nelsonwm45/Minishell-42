/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:58:34 by nchok             #+#    #+#             */
/*   Updated: 2024/11/26 12:31:45 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../header/minishell.h"

/*
	create a lexer node
	delete the node with the redirections
	add redirections to the back of redirection list
*/
int		add_redirections(t_parser *parser, t_lexer *ptr)
{
	t_lexer	*node;
	int		i;
	int		j;

	node = create_node(ft_strdup(ptr->next->str), ptr->token_type);
	if (!node)
		parsing_error(1, parser->utils, parser->lexer_list);
	add_to_backlexer(node, &parser->redirections);
	i = ptr->i;
	j = ptr->next->i;
	del_one_node(&parser->lexer_list, i);
	del_one_node(&parser->lexer_list, j);
	parser->redirections_count++;
	return (0);
}

/*
	recognize the redirections
	delete the redirections from the lexer list
	and add them to the back of of the redirection list

	@error handling
	if next token of redirection is null, output 'newline' error
	if next token is token, output 'unexpected token 'next'' error
*/
void	recog_redirections(t_parser *parser)
{
	t_lexer *ptr;

	ptr = parser->lexer_list;
	while (ptr && ptr->token_type == 0) // skip words token
		ptr = ptr->next;
	if (!ptr || ptr->token_type == PIPE) // empty or pipe token
		return ;
	if (!ptr->next) // if next is NULL
		parsing_error(1, parser->utils, parser->utils->lexer_list);
	if (ptr->next->token_type)
		double_token_error(parser->lexer_list, ptr->next->token_type);
	if (ptr->token_type >= BIG && ptr->token_type <= SMALLSMALL) // check if token is redirections
		add_redirections(parser, ptr);
	recog_redirections(parser);
}
