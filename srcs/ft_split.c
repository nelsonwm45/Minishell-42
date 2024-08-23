/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:34:54 by hheng             #+#    #+#             */
/*   Updated: 2024/07/03 08:52:48 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

static int	is_sep(char c, char charset)
{
	return (c == charset || c == '\0');
}

static int	get_size(const char *str, char sep)
{
	int	i;
	int	length;

	i = -1;
	length = 0;
	while (str[++i])
	{
		if (!is_sep(str[i], sep) && is_sep(str[i + 1], sep))
			length++;
	}
	return (length);
}

static void	str_putword(char *dest, const char *src, char sep)
{
	int	i;

	i = -1;
	while (!is_sep(src[++i], sep))
		dest[i] = src[i];
	dest[i] = '\0';
}

static void	insert_words(char **arr, const char *str, char sep)
{
	int	i;
	int	j;
	int	w_count;

	i = 0;
	w_count = 0;
	while (str[i] != '\0')
	{
		if (is_sep(str[i], sep))
			i++;
		else
		{
			j = 0;
			while (!is_sep(str[i + j], sep))
				j++;
			arr[w_count] = (char *)malloc(j + 1);
			str_putword(arr[w_count], str + i, sep);
			i = i + j;
			w_count++;
		}
	}
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		total_size;

	if (!s)
		return (NULL);
	total_size = get_size(s, c);
	arr = (char **)malloc(sizeof(char *) * (total_size + 1));
	if (!arr)
		return (NULL);
	insert_words(arr, s, c);
	arr[total_size] = 0;
	return (arr);
}
