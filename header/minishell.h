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

/* Macros */
/* Standard Library */
// # include "../readline/x86_64/include/readline/readline.h"
// # include "../readline/x86_64/include/readline/history.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>  // For strerror
# include <limits.h>  // For PATH_MAX

/* Constants */
# define ERROR 1
# define SUCCESS 0
# define BUFF_SIZE 1000

/* Structs */
typedef struct	s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct s_env
{
    char            *value;
    struct s_env    *next;
}               t_env;

typedef struct s_shell
{
	t_token			*token_list;
	t_env			*env_vars;
	t_env			*hidden_env_vars;

	int				input_fd;
	int				output_fd;
	int				default_input_fd;
	int				default_output_fd;
	int				pipe_input_fd;
	int				pipe_output_fd;

	int				process_id;
	int				process_charge;
	int				is_parent_process;
	int				is_last_command;
	int				return_code;
	int				exit_code;
	int				skip_execution;

} t_shell;


/* Functions */
void	print_welcome(void);
int		same_str(char *s1, char *s2);
static void print_error(char *arg);
static char *get_env_path(t_env *env, const char *var_name) ;
int     update_oldpwd(t_env *env);
int     go_to_path(int option, t_env *env);
int     ft_cd(char **args, t_env *env);

/* Test */

#endif