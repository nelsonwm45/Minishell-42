/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:09:52 by hheng             #+#    #+#             */
/*   Updated: 2024/07/03 08:44:19 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"


char	*ft_strjoin_special(char const *s1, char const *s2, int bytes_read)
{
	char	*str;
	int		s1_len;
	int		i;

	if (!s1)
		s1_len = 0;
	else
		s1_len = ft_strlen(s1);
	i = -1;
	str = malloc((s1_len + bytes_read + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (s1_len != 0)
	{
		while (s1[++i])
			str[i] = s1[i];
		i--;
	}
	while (++i - s1_len < bytes_read)
		str[i] = s2[i - s1_len];
	str[s1_len + bytes_read] = '\0';
	return (str);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	char	*temp;
	int		len;
	int		i;

	len = BUFFER_SIZE;
	temp = (char *)s;
	i = -1;
	while (++i <= len)
		if (temp[i] == (char)c)
			return (&temp[i]);
	return (NULL);
}

char	*ft_strdup_gnl(const char *s1)
{
	int		i;
	char	*str;

	str = (char *)malloc(ft_strlen((char *)s1) + 1);
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		str[i] = s1[i];
	str[i] = '\0';
	return (str);
}

int	line_len(char *buffer)
{
	int	len;

	len = 0;
	while (*buffer != '\n' && *buffer)
	{
		len++;
		buffer++;
	}
	if (*buffer == '\n')
		len++;
	return (len);
}
