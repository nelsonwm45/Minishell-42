/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:27:54 by hheng             #+#    #+#             */
/*   Updated: 2024/11/05 13:27:54 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Calculates the number of strings (lines) in a given 
//	array of environment variables.
int	str_env_len(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

/*

@brief : Sorts an array of strings (environment variables) 
in  (alphabetical) order.

1. Use a bubble sort algorithm to repeatedly compare
	and swap adjacent strings if they are not in order (ft_strcmp).
2. Continue until no swaps are needed (indicated by ordered being 1).
3. Reduce the length to optimize the sorting process (env_len--) 
	as the largest elements are already in place.
*/
void	sort_env(char **tab, int env_len)
{
	int		ordered;
	int		i;
	char	*tmp;

	ordered = 0;
	while (tab && ordered == 0)
	{
		ordered = 1;
		i = 0;
		while (i < env_len - 1)
		{
			if (ft_strcmp(tab[i], tab[i + 1]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
				ordered = 0;
			}
			i++;
		}
		env_len--;
	}
}

/*
@brief : Prints all environment variables in sorted order with the 
	prefix declare -x.

1. Prints all environment variables in sorted order with the 
	prefix declare -x.
2. Split the string into an array of strings (tab) using ft_split.
3. Free the string after splitting (ft_memdel(str_env)).
4. Sort the array using sort_env.
5. Iterate through the sorted array:
6. Print each string prefixed by declare -x 
7. Free the array using free_tab.
*/
void	print_sorted_env(t_env *env)
{
	int		i;
	char	**tab;
	char	*str_env;

	str_env = env_to_str(env);
	tab = ft_split(str_env, '\n');
	ft_memdel(str_env);
	sort_env(tab, str_env_len(tab));
	i = 0;
	while (tab[i])
	{
		ft_putstr("declare -x ");
		ft_putendl(tab[i]);
		i++;
	}
	free_tab(tab);
}
