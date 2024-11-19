/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:33:18 by nchok             #+#    #+#             */
/*   Updated: 2024/11/12 11:33:18 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* Own Library */
# include "../libft/libft.h"
# include "./color.h"

/* Macros */
/* Standard Library */
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h> // For PATH_MAX
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h> // For signal handling
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h> // For strerror
# include <sys/wait.h>
# include <unistd.h>

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
	PIPE = 1,
	BIG,
	BIGBIG,
	SMALL,
	SMALLSMALL,
} t_type;

typedef enum s_builtin
{
	NOT_BUILTIN = 0,
	CD,
	ECHO,
	ENV,
	EXPORT,
	PWD,
	UNSET,
	EXIT,
} t_builtin;

typedef struct s_env
{
	char *value;
	struct s_env *next;
} t_env;

typedef struct s_token
{
	char *str;
	int type;
	struct s_token *prev;
	struct s_token *next;
} t_token;

typedef struct s_lexer
{
	t_type token_type;
	char *str;
	int i;
	struct s_lexer *prev;
	struct s_lexer *next;
} t_lexer;

typedef struct s_cmds
{
	char **str;
	int redir_count;
	char *hd_file_name;
	t_builtin builtin;
	t_lexer *redir;
	struct s_cmds *next;
	struct s_cmds *prev;
} t_cmds;

typedef struct s_parser
{
	t_lexer *lexer_list;
	t_lexer *redirections;
	int redirections_count;
	struct s_general *utils;
} t_parser;

typedef struct s_general
{
	t_env *env_vars;
	struct s_shell *mini;

	t_lexer *lexer_list;
	t_cmds *cmds;
	char *line;
	int pipecount;
	int in_cmd;
	int *pid;
	int reset;
	int exit_status;
	int stop_heredoc;
	int	in_heredoc;
	int	heredoc;

	char **envp;
	char **path;
	char *pwd;
	char *oldpwd;

} t_general;

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

typedef struct s_expansions
{
	char *new_arg;
	int i;
	int j;
} t_expansions;

/* Functions */
// void	print_welcome(void);
int	same_str(char *s1, char *s2);
int	start_shell(t_general *utils);
// t_token *create_token_from_cmd(t_cmds *cmd);
int	closed_quotes(char *line);
int	find_next_quote(char *line, int *i, int *num_quote, char quote);
void	exec_cmd_from_token(t_shell *mini, t_token *token);

/* Token */
int	init_utils(t_general *utils);
int	read_token(t_general *utils);
int	is_spaces(char c);
int	remove_space(char *line, int *i);
int	is_token(char c);
t_type	get_token_type(int c);
int	handle_token(char *str, int i, t_lexer **lexer_list);
int	handle_word(char *str, int i, t_lexer **lexer_list);
int	handle_quotes(int i, char *str, char quote);

/* Env Functions */
int	process_envp(char **envp, t_general *utils);
char	**duplicate_env(char **envp);
// int	get_pwd(t_general *utils);
int	print_envp(t_general *utils); // debug purpose

/* Error Functions */
int	double_token_error(t_general *utils, t_lexer *lexer, t_type token_type);
void	parsing_error(int error, t_general *utils, t_lexer *lexer);
int	pipes_errors(t_general *utils, t_type token_type);

/* Cleanning Structs */
void	free_array(char **arr);
int	clean_utils(t_general *utils);
int	clean_lexer(t_lexer **lexer);

int	error_message(int error_code, t_general *utils);
/* Lexer Functions */
int	add_node_to_lexer(char *str, t_type token_type, t_lexer **lexer_list);
int	add_to_backlexer(t_lexer *node, t_lexer **lexer_list);
t_lexer	*create_node(char *str, t_type token_type);

/* Lexer Cleaning Functions*/
void	del_one_node(t_lexer **lexer, int i);
void	del_first_node(t_lexer **lexer);
t_lexer	*clear_node(t_lexer **lexer);

/* Parser Functions */
int	count_pipes(t_general *utils);
int	pipes_errors(t_general *utils, t_type token_type);
t_parser	init_parser(t_general *utils, t_lexer *lexer_list);
int	start_parsing(t_general *utils);

/* Parsing - Commands Structs */
t_cmds	*init_cmds(t_parser *parser);
t_cmds	*create_cmds(char **str, t_lexer *redirections, int redir_count);
t_builtin	check_builtin(char *str);
char	**form_str(char **str, int size, t_parser *parser);
void	add_to_backcmds(t_cmds **parse_cmds, t_cmds *utils_cmds);
int	count_no_pipe(t_lexer *lexer_list);

/* Parsing - Redirections */
void	recog_redirections(t_parser *parser);
int	add_redirections(t_parser *parser, t_lexer *ptr);

/* Executions Setup */
int	setup_executor(t_general *utils);
int	prep_builtin(t_general *utils, t_cmds *cmds, t_shell *mini);

/* Execution */
void	exec_simple_cmd(t_general *utils, t_cmds *cmds);
int		exec_complex_cmd(t_general *utils);
void	handle_cmd(t_general *utils, t_cmds *cmds);
int	search_cmd(t_general *utils, t_cmds *cmds);
int		cmd_not_found(char *cmd);
char	*join_split_str(char **split_str, char *new_str);
char	**resplit_str(char **double_arr);

/* Pipe */
void	dup2_cmd(t_cmds *cmds, t_general *utils, int pipe_fd[2], int fd_in);
int		wait_pipe(t_general *utils, int *pid, int pipecount);
t_cmds	*travel_first_cmds(t_cmds *cmds);

int	check_fd_heredoc(t_general *utils, t_cmds *cmds, int pipe_fd[2]);
int	ft_fork(t_general *utils, int pipe_fd[2], int fd_in, t_cmds *cmds);



/* Expander */
t_cmds	*call_expander(t_general *utils, t_cmds *cmds);
char	**expander(t_general *utils, char **str);
char	*replace_to_env(t_general *utils, char *str);
int	find_dollar(char *str);
char	*replace_to_env(t_general *utils, char *str);
int	subs_dollar_var(t_general *utils, char *str, char **tmp, int j);
int	append_str(char **tmp, char **tmp2, char **tmp3, int j);
int	dollar_str_len(char *str, int j);
int	get_equal_sign_index(char *str);
int	replace_question_mark(t_general *utils, char **tmp);
int	skipped_char_after_dollar(int j, char *str);
char	*remove_quotes(char *str, char quote);
char	*expand_str(t_general *utils, char *str);
char	*char_to_str(char c);

/* Heredoc */
int	start_heredoc(t_general *utils, t_cmds *cmds);
char	*create_hd_filename(void);
int	mini_heredoc(t_general *utils, t_lexer *ptr, char *filename);
int	create_heredoc(t_general *utils, t_lexer *ptr, char *filename, int have_quote);

/* Redirections */
int	check_redir(t_cmds *cmds);
int	handle_infile(char *filename);
int	handle_outfile(t_lexer *redir);
int	append_or_trunc(t_lexer *redir);

/* Helper Functions */
void	init_signal(t_general *utils);
void	sigint_handler(int sig);

/* Printing Functions */
void	print_lexer(t_general *utils);
void	print_cmds(t_general *utils);

/* Builtin Functions */
int	ft_cd(char **args, t_env *env);
int	ft_env(t_env *env);
int	ft_echo(char **args);
char	*get_env_name(char *dest, const char *src);
int	is_in_env(t_env *env, char *args);
int	ft_pwd(void);
int	env_add(const char *value, t_env *env);
int	is_valid_env(const char *env);
int	ft_unset(char **args, t_shell *mini);
void	ft_exit(t_shell *mini, char **cmd);
int	ft_export(char **args, t_env *env, t_env *secret);
int	update_oldpwd(t_env *env);
int	go_to_path(int option, t_env *env);

/* Environment Function*/
size_t	size_env(t_env *lst);
void	ft_putendl(char *s);
char	*env_to_str(t_env *lst);
int	env_init(t_shell *mini, char **env_array);
int	secret_env_init(t_shell *mini, char **env_array);
int	is_env_char(int c);
int	env_value_len(const char *env);
char	*env_value(char *env);
char	*get_env_value(char *var_name, t_env *env);
void	increment_shell_level(t_env *env);
int	str_env_len(char **env);
void	sort_env(char **tab, int env_len);
void	print_sorted_env(t_env *env);

/* Tools utils*/
void	free_tab(char **tab);
void	ft_putendl(char *s);
char	*path_join(const char *s1, const char *s2);
char	*check_dir(char *bin, char *command);
int	arg_alloc_len(const char *arg, t_env *env, int ret);
int	get_var_len(const char *arg, int i, t_env *env, int ret);

/*Signal Function*/
void	sigint_handler(int sig);
void	sig_int(int code);
void	sig_quit(int code);
void	sig_init(void);
void	free_token(t_token *token);
int	magic_box(char *path, char **args, t_env *env, t_shell *mini, pid_t *pid, int *sigint, int *sigquit);
#endif