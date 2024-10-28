/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:21:38 by nchok             #+#    #+#             */
/*   Updated: 2024/10/28 15:40:13 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# include "./minishell.h"

typedef struct s_lexer
{
	char			*str;
	t_token			token_type;
	int				i;
	struct s_lexer	*prev;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_simple_cmds
{
	char					**str;
	int						num_redir;
	char					*hd_file_name;
	t_lexer					*redir;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}	t_simple_cmds;

typedef struct s_general
{
	t_lexer			*lexer_list;
	t_simple_cmds	*cmds_list;
	char			**envp;
	char			**path;
	char			*pwd;
	char			*oldpwd;
	char			*line;
}	t_general;

int	process_envp(char **envp, t_general *utils);
int	duplicate_env(char **envp, t_general *utils);
int	get_pwd(t_general *utils);
int	print_envp(t_general *utils); // debug purpose
int	init_utils(t_general *utils);

#endif