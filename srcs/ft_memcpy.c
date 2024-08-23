/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:19:49 by hheng             #+#    #+#             */
/*   Updated: 2024/07/03 08:50:56 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*p_dest;
	char	*p_src;

	if (!dst && !src)
		return (dst);
	p_dest = (char *) dst;
	p_src = (char *) src;
	i = -1;
	while (++i < n)
		p_dest[i] = p_src[i];
	return (dst);
}
