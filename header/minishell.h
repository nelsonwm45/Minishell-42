/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:11:05 by nchok             #+#    #+#             */
/*   Updated: 2024/09/05 00:39:15 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* Own Library */
# include "../libft/libft.h"
# include "./color.h"
# include "./builtin.h"
# include "./env.h"
# include "./helper.h"
# include "./error.h"

/* Standard Library */
// # include "../readline/x86_64/include/readline/readline.h"
// # include "../readline/x86_64/include/readline/history.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <signal.h>

# define ERROR -1
# define TRUE 1
# define FALSE 0

typedef enum s_token
{
	PIPE = 1,
	BIG,
	BIGBIG,
	SMALL,
	SMALLSMALL,
}	t_token;

/* Functions */
// void	print_welcome(void);
int		same_str(char *s1, char *s2);
int		start_shell(t_general *utils);
int		closed_quotes(char *line);
int		find_next_quote(char *line, int *i, int *num_quote, char quote);

/* Token */
int		read_token(t_general *utils);
int		is_spaces(char c);
int		remove_space(char *line, int *i);
int		is_token(char c);
t_token	get_token_type(int c);
int		handle_token(char *str, int i, t_lexer **lexer_list);
int		handle_word(char *str, int i, t_lexer **lexer_list);
int		handle_quotes(int i, char *str, char quote);

/* Test */

#endif
