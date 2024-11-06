/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:11:05 by nchok             #+#    #+#             */
/*   Updated: 2024/10/28 15:41:10 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* Own Library */
# include "../libft/libft.h"
# include "./color.h"

/* Macros */
/* Standard Library */
# include <stdlib.h>
# include <errno.h>
# include <stdint.h>
# include <limits.h> // For PATH_MAX
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h> // For signal handling
# include <stdio.h>
# include <string.h> // For strerror
# include <unistd.h>
#include <stdbool.h>
#include <dirent.h>
# include <fcntl.h>

/* Constants */
# define ERROR -1
# define SUCCESS 0
# define TRUE 1
# define FALSE 2
# define BUFF_SIZE 1000
# define END_TOKEN 3
# define COMMAND 4
# define UNKNOWN_COMMAND 127
# define IS_DIRECTORY 126

/* Structs */
typedef enum s_type
{
    PIPE = 6,
    BIG,
    BIGBIG,
    SMALL,
    SMALLSMALL,
} t_type;

typedef struct s_token
{
    char *str;
    int type;
    struct s_token *prev;
    struct s_token *next;
} t_token;

typedef struct s_lexer
{
    char *str;
    t_type token_type;
    int i;
    struct s_lexer *prev;
    struct s_lexer *next;
} t_lexer;

typedef struct s_simple_cmds
{
    char **str;
    int num_redir;
    char *hd_file_name;
    t_lexer *redir;
    struct s_simple_cmds *next;
    struct s_simple_cmds *prev;
} t_simple_cmds;

typedef struct s_general
{
    t_lexer *lexer_list;
    t_simple_cmds *cmds_list;
    char **envp;
    char **path;
    char *pwd;
    char *oldpwd;
    char *line;
} t_general;

typedef struct s_env
{
    char *value;
    struct s_env *next;
} t_env;

typedef struct s_shell
{
    t_token *token_list;
    t_env *env_vars;
    t_env *hidden_env_vars;

    int input_fd;
    int output_fd;
    int default_input_fd;
    int default_output_fd;
    int pipe_input_fd;
    int pipe_output_fd;

    int process_id;
    int process_charge;
    int is_parent_process;
    int is_last_command;
    int return_code;
    int exit_code;
    int skip_execution;

} t_shell;

typedef struct	s_expansions
{
	char			*new_arg;
	int				i;
	int				j;
}				t_expansions;

/* Functions */
// void	print_welcome(void);
int	same_str(char *s1, char *s2);
int	start_shell(t_general *utils);
int	closed_quotes(char *line);
int	find_next_quote(char *line, int *i, int *num_quote, char quote);

/* Token */
int	read_token(t_general *utils);
int	is_spaces(char c);
int	remove_space(char *line, int *i);
int	is_token(char c);
t_type	get_token_type(int c);
int	handle_token(char *str, int i, t_lexer **lexer_list);
int	handle_word(char *str, int i, t_lexer **lexer_list);
int	handle_quotes(int i, char *str, char quote);
int	update_oldpwd(t_env *env);
int	go_to_path(int option, t_env *env);
int	ft_cd(char **args, t_env *env);

int env_add(const char *value, t_env *env);

/* Error Functions */
void	free_array(char **arr);
int	clean_utils(t_general *utils);
int	error_message(int error_code, t_general *utils);

/* Lexer Functions */
int	add_node_to_lexer(char *str, t_type token_type, t_lexer **lexer_list);
int	add_to_backlexer(t_lexer *node, t_lexer **lexer_list);
t_lexer	*create_node(char *str, t_type token_type);

/* Helper Functions */
void	init_signal(t_general *utils);
void	sigint_handler(int sig);

/* Builtin Functions */
int	ft_cd(char **args, t_env *env);
int	ft_env(t_env *env);
int	ft_echo(char **args);
char *get_env_name(char *dest, const char *src);
int	 is_in_env(t_env *env, char *args);
int	env_add(const char *value, t_env *env);
int	ft_pwd(void);
int		is_valid_env(const char *env);
int	ft_unset(char **args, t_shell *mini);
void	mini_exit(t_shell *mini, char **cmd);
int	ft_export(char **args, t_env *env, t_env *secret);

/* Environment Function*/
size_t	size_env(t_env *lst);
void	ft_putendl(char *s);
char	*env_to_str(t_env *lst);
int	env_init(t_shell *mini, char **env_array);
int	secret_env_init(t_shell *mini, char **env_array);
int	is_env_char(int c);
int	env_value_len(const char *env);
char	*env_value(char *env);
char *get_env_value(char *var_name, t_env *env);
void	increment_shell_level(t_env *env);
int	str_env_len(char **env);
void	sort_env(char **tab, int env_len);
void	print_sorted_env(t_env *env);
int	duplicate_env(char **envp, t_general *utils);
int	get_pwd(t_general *utils);
int	print_envp(t_general *utils); // debug purpose
int	init_utils(t_general *utils);
int	get_oldpwd(t_general *utils);
int	get_array_size(char **arr);
void	store_path(t_general *utils);
int	process_envp(char **envp, t_general *utils);
char *get_path(t_general *utils);

/* Execution Functions */

void	ft_close(int fd);
int			exec_bin(char **args, t_env *env, t_shell *mini);
char *expansions(char *arg, t_env *env, int ret);
bool is_end_of_command(t_token *token);
int	is_builtin(char *command);
int	exec_builtin(char **args, t_shell *mini);
char **cmd_tab(t_token *start);
void exec_cmd(t_shell *mini, t_token *token);
int		has_pipe(t_token *token);


/* Tools utils*/
void	free_tab(char **tab);
void	ft_putendl(char *s);
char		*path_join(const char *s1, const char *s2);
char		*check_dir(char *bin, char *command);
int		arg_alloc_len(const char *arg, t_env *env, int ret);

/*Signal Function*/
void	sigint_handler(int sig);
void sig_int(int code);
void sig_quit(int code);
void sig_init(void);
void free_token(t_token *token);
int magic_box(char *path, char **args, t_env *env, t_shell *mini, pid_t *pid, int *sigint, int *sigquit);

#endif