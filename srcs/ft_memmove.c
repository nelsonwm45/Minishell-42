/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:11:09 by hheng             #+#    #+#             */
/*   Updated: 2024/07/03 08:51:13 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*p_dest;
	unsigned char	*p_src;

	p_dest = (unsigned char *) dst;
	p_src = (unsigned char *) src;
	if (!dst && !src)
		return (NULL);
	if (dst > src)
	{
		p_dest += len;
		p_src += len;
		while (len--)
			*--p_dest = *--p_src;
	}
	else
		while (len--)
			*p_dest++ = *p_src++;
	return (dst);
}
