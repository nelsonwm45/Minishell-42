/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:49:29 by hheng             #+#    #+#             */
/*   Updated: 2024/07/03 08:56:04 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char c, char const *set)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	int		i;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	start = 0;
	end = ft_strlen(s1);
	while (s1[i] && is_set(s1[i], set))
	{
		i++;
		start++;
	}
	i = ft_strlen(s1) - 1;
	while (start < end && is_set(s1[i], set))
	{
		i--;
		end--;
	}
	return (ft_substr(s1, start, end - start));
}
