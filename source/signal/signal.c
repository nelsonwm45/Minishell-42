/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:19:48 by nchok             #+#    #+#             */
/*   Updated: 2024/10/28 15:43:06 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static int sigint;
static int sigquit;
static pid_t pid;
static int exit_status;

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sig_int(int code)
{
	(void)code;
	if (pid == 0)
	{
		ft_putstr_fd("\b\b  ", 2);
		ft_putstr_fd("\n", 2);
		ft_putstr_fd("\033[0;36m\033[1m🤬 minishell ▸ \033[0m", 2);
		exit_status = 1;
	}
	else
	{
		ft_putstr_fd("\n", 2);
		exit_status = 130;
	}
	sigint = 1;
}

void	sig_quit(int code)
{
	char	*nbr;

	nbr = ft_itoa(code);
	if (pid != 0)
	{
		ft_putstr_fd("Quit: ", 2);
		ft_putendl_fd(nbr, 2);
		exit_status = 131;
		sigquit = 1;
	}
	else
		ft_putstr_fd("\b\b  \b\b", 2);
	ft_memdel(nbr);
}

void	sig_init(void)
{
	sigint = 0;
	sigquit = 0;
	pid = 0;
	exit_status = 0;
}

void free_token(t_token *token)
{
    t_token *temp;

    while (token)
    {
        temp = token;
        token = token->next;
        free(temp->str);
        free(temp);
	}
}

int magic_box(char *path, char **args, t_env *env, t_shell *mini, pid_t *pid, int *sigint, int *sigquit)
{
    char **env_array;
    char *ptr;
    int ret;

    ret = SUCCESS;
    *pid = fork();
    if (*pid == 0)
    {
        ptr = env_to_str(env);
        env_array = ft_split(ptr, '\n');
        ft_memdel(ptr);
        if (ft_strchr(path, '/') != NULL)
            execve(path, args, env_array);
        ret = error_message_path(path);
        free_tab(env_array);
        free_token(mini->token_list);
        exit(ret);
    }
    else
        waitpid(*pid, &ret, 0);
    if (*sigint == 1 || *sigquit == 1)
        return (exit_status);
    ret = (ret == 32256 || ret == 32512) ? ret / 256 : !!ret;
    return (ret);
}