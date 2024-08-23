/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:54:12 by hheng             #+#    #+#             */
/*   Updated: 2024/07/03 08:53:03 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*temp;
	int		len;
	int		i;

	len = ft_strlen((char *) s);
	temp = (char *) s;
	i = -1;
	while (++i <= len)
		if (temp[i] == (char) c)
			return (&temp[i]);
	return (NULL);
}
