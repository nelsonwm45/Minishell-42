/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:21:38 by nchok             #+#    #+#             */
/*   Updated: 2024/10/16 16:41:46 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# include "./minishell.h"

typedef struct s_env
{
	char	**envp;
	char	**path;
	char	*pwd;
	char	*oldpwd;
	char	*line;
}	t_env;

int	process_envp(char **envp, t_env *utils);
int	duplicate_env(char **envp, t_env *utils);
int	get_pwd(t_env *utils);
int	print_envp(t_env *utils); // debug purpose

#endif