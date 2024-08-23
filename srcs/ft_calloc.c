/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 18:15:31 by hheng             #+#    #+#             */
/*   Updated: 2024/07/03 08:45:07 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*arr;

	if (count && size && count > INT_MAX / size)
		return (NULL);
	arr = malloc(count * size);
	if (!arr)
		return (arr);
	ft_bzero(arr, count * size);
	return (arr);
}
