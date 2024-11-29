/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:55:02 by nchok             #+#    #+#             */
/*   Updated: 2024/11/26 17:04:51 by nchok            ###   ########.fr       */
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
