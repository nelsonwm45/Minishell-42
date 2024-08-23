/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:22:59 by hheng             #+#    #+#             */
/*   Updated: 2024/07/22 13:22:59 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi_base(const char *str, const char *base)
{
	int	nb;
	int	sign;

	nb = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str++ == '-')
			sign *= -1;
	}
	while (ft_strchr_i(base, *str) != -1
		|| ft_strchr_i(base, ft_toupper(*str)) != -1)
	{
		if (ft_strchr_i(base, *str) != -1)
			nb = nb * ft_strlen(base) + ft_strchr_i(base, *str++);
		else
			nb = nb * ft_strlen(base) + ft_strchr_i(base, ft_toupper(*str++));
	}
	return (nb * sign);
}
