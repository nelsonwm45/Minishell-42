/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:03:07 by hheng             #+#    #+#             */
/*   Updated: 2024/07/03 08:55:49 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*temp;
	char	*final_str;
	int		len;
	int		i;

	len = ft_strlen((char *) s);
	temp = (char *) s;
	i = -1;
	final_str = (NULL);
	while (++i <= len)
		if (temp[i] == (char) c)
			final_str = &temp[i];
	return (final_str);
}
