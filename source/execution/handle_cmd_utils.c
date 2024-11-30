/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:55:02 by nchok             #+#    #+#             */
/*   Updated: 2024/11/30 12:58:43 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/*
	function to join a str with space in double array

	return a new long str with spaces
*/
char	*join_split_str(char **split_str)
{
	char	*tmp;
	char	*str_space;
	int		i;

	tmp = ft_strdup(split_str[0]);
	i = 1;
	while (split_str[i])
	{
		str_space = ft_strjoin(tmp, " ");
		free(tmp);
		tmp = ft_strjoin(str_space, split_str[i]);
		free(str_space);
		i++;
	}
	return (tmp);
}

/*
	Free the initial double array, combine its strings into a single string, 
	and split it back into a new double array.
*/
char	**resplit_str(char **double_arr)
{
	char	**ret_str;
	char	*joined_str;

	if (!double_arr)
		return (NULL);
	joined_str = join_split_str(double_arr);
	free_array(double_arr);
	ret_str = ft_split(joined_str, ' ');
	free(joined_str);
	return (ret_str);
}

char	**find_path(t_env *env)
{
	char	*path;
	char	**path_arr;
	t_env	*ptr;

	ptr = env;
	path = NULL;
	while (ptr)
	{
		if (!ft_strncmp(ptr->value, "PATH=", 5))
		{
			path = ft_strdup(ptr->value + 5);
			break ;
		}
		ptr = ptr->next;
	}
	if (!path)
		return (NULL);
	path_arr = ft_split(path, ':');
	free(path);
	path_arr = make_dir(path_arr);
	return (path_arr);
}

char	**make_dir(char **path_arr)
{
	int		i;
	char	*temp;

	i = 0;
	while (path_arr[i])
	{
		if (path_arr[i][ft_strlen(path_arr[i]) - 1] != '/')
		{
			temp = path_arr[i];
			path_arr[i] = ft_strjoin(path_arr[i], "/");
			free(temp);
		}
		i++;
	}
	path_arr[i] = NULL;
	return (path_arr);
}