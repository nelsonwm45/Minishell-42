/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:26:55 by hheng             #+#    #+#             */
/*   Updated: 2024/11/05 13:26:55 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void print_error(char **args)
{
    ft_putstr_fd("cd: ", 2);
    if (args[2])
        ft_putstr_fd("string not in pwd: ", 2);
    else
    {
        ft_putstr_fd(strerror(errno), 2);
        ft_putstr_fd(": ", 2);
    }
    ft_putendl_fd(args[1], 2);
}

static char *get_env_path(t_env *env, const char *var, size_t len)
{
    char *oldpwd;
    int i;
    int j;
    int s_alloc;

    while (env && env->next != NULL)
    {
        if (ft_strncmp(env->value, var, len) == 0 && env->value[len] == '=')
        {
            s_alloc = ft_strlen(env->value) - len;
            oldpwd = malloc(sizeof(char) * (s_alloc + 1));
            if (!oldpwd)
            {
                perror("malloc");
                return (NULL);
            }
            i = 0;
            j = 0;
            while (env->value[i++])
            {
                if (i > (int)len)
                    oldpwd[j++] = env->value[i];
            }
            oldpwd[j] = '\0';
            return (oldpwd);
        }
        env = env->next;
    }
    return (NULL);
}

int update_oldpwd(t_env *env)
{
    char cwd[PATH_MAX];
    char *oldpwd;

    if (getcwd(cwd, PATH_MAX) == NULL)
        return (ERROR);

    oldpwd = ft_strjoin("OLDPWD=", cwd);
    if (!oldpwd)
    {
        perror("ft_strjoin");
        return (ERROR);
    }
    if (is_in_env(env, oldpwd) == 0)
    {
        printf("Adding OLDPWD to env\n");
        env_add(oldpwd, env);
    }
    else
    {
        t_env *current = env;
        while (current)
        {
            if (ft_strncmp(current->value, "OLDPWD=", 7) == 0)
            {
                printf("Updating OLDPWD in env\n");
                free(current->value);  // Ensure current->value was dynamically allocated before freeing
                current->value = oldpwd;
                break;
            }
            current = current->next;
        }
    }
    return (SUCCESS);
}


int go_to_path(int option, t_env *env)
{
    int ret;
    char *env_path;

    env_path = NULL;
    if (option == 0)
    {
        update_oldpwd(env);
        env_path = get_env_path(env, "HOME", 4);
        if (!env_path)
        {
            ft_putendl_fd("minishell : cd: HOME not set", 2);
            return (ERROR);
        }
    }
    else if (option == 1)
    {
        env_path = get_env_path(env, "OLDPWD", 6);
        if (!env_path)
        {
            ft_putendl_fd("minishell : cd: OLDPWD not set", 2);
            return (ERROR);
        }
        update_oldpwd(env);
    }
    ret = chdir(env_path);
    if (ret == -1)
    {
        perror("chdir");
    }
    free(env_path);
    return (ret);
}

int ft_cd(char **args, t_env *env)
{
    int cd_ret;

    printf("Executing cd command\n");

    if (!args[1])
    {
        printf("No arguments provided, going to HOME\n");
        return (go_to_path(0, env));
    }
    if (ft_strcmp(args[1], "-") == 0)
    {
        printf("Argument is '-', going to OLDPWD\n");
        cd_ret = go_to_path(1, env);
    }
    else
    {
        printf("Changing directory to: %s\n", args[1]);
        update_oldpwd(env);
        cd_ret = chdir(args[1]);
        if (cd_ret < 0)
        {
            perror("chdir");
            cd_ret *= -1;
        }
        if (cd_ret != 0)
            print_error(args);
    }
    return (cd_ret);
}