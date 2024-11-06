/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:24:28 by hheng             #+#    #+#             */
/*   Updated: 2024/11/05 17:24:28 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void insert_var(t_expansions *ex, char *arg, t_env *env, int ret)
{
    char *env_value;
    int k;

    // Check if we're expanding `$?`, which means the last return code
    if (arg[ex->j] == '?')
    {
        char *ret_str = ft_itoa(ret);  // Convert ret to string
        if (ret_str)
        {
            k = 0;
            while (ret_str[k] != '\0')
            {
                ex->new_arg[ex->i++] = ret_str[k++];
            }
            free(ret_str);
        }
        ex->j++;  // Move past the `?`
        return;
    }

    // Expand other environment variables
    env_value = get_env_value(arg + ex->j, env);

    if (env_value && *env_value != '\0')
    {
        k = 0;
        while (env_value[k] != '\0')
        {
            ex->new_arg[ex->i++] = env_value[k++];
        }
    }

    ft_memdel(env_value);  // Free memory after use

    // Move `ex->j` forward based on the variable name structure
    if (!ft_isdigit(arg[ex->j]) && arg[ex->j - 1] != '?')
    {
        while (ft_isalnum(arg[ex->j]) || arg[ex->j] == '_')
        {
            ex->j++;
        }
    }
    else if (arg[ex->j - 1] != '?')
    {
        ex->j++;
    }
}


char *expansions(char *arg, t_env *env, int ret)
{
    t_expansions ex;
    int new_arg_len;

    new_arg_len = arg_alloc_len(arg, env, ret);
    if (!(ex.new_arg = malloc(sizeof(char) * (new_arg_len + 1))))
        return (NULL);
    ex.i = 0;
    ex.j = 0;
    while (ex.i < new_arg_len && arg[ex.j])
    {
        while (arg[ex.j] == '$')  // Directly using '$' instead of EXPANSION
        {
            ex.j++;
            if ((arg[ex.j] == '\0' || ft_isalnum(arg[ex.j]) == 0) && arg[ex.j] != '?')
                ex.new_arg[ex.i++] = '$';
            else
                insert_var(&ex, arg, env, ret);
        }
        ex.new_arg[ex.i++] = arg[ex.j++];
    }
    ex.new_arg[ex.i] = '\0';
    return (ex.new_arg);
}

int exec_bin(char **args, t_env *env, t_shell *mini)
{
    int i;
    char **bin;
    char *path;
    int ret;
    pid_t pid;
    int sigint = 0;
    int sigquit = 0;

    i = 0;
    ret = UNKNOWN_COMMAND;
    while (env && env->value && ft_strncmp(env->value, "PATH=", 5) != 0)
        env = env->next;
    if (env == NULL || env->next == NULL)
        return (magic_box(args[0], args, env, mini, &pid, &sigint, &sigquit));
    bin = ft_split(env->value, ':');
    if (!args[0] && !bin[0])
        return (ERROR);
    i = 1;
    path = check_dir(bin[0] + 5, args[0]);
    while (args[0] && bin[i] && path == NULL)
        path = check_dir(bin[i++], args[0]);
    if (path != NULL)
        ret = magic_box(path, args, env, mini, &pid, &sigint, &sigquit);
    else
        ret = magic_box(args[0], args, env, mini, &pid, &sigint, &sigquit);
    free_tab(bin);
    ft_memdel(path);
    return (ret);
}

void	ft_close(int fd)
{
	if (fd > 0)
		close(fd);
}

int		is_type(t_token *token, int type)
{
	if (token && token->type == type)
		return (1);
	else
		return (0);
}

int		has_pipe(t_token *token)
{
	while (token && is_type(token, END_TOKEN) == 0)
	{
		if (is_type(token, PIPE))
			return (1);
		token = token->next;
	}
	return (0);
}

