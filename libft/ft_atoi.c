/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:46:13 by hheng             #+#    #+#             */
/*   Updated: 2024/07/03 08:44:37 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	i;
	int	num;
	int	is_negative;

	i = -1;
	num = 0;
	is_negative = 0;
	while (*str == '\n' || *str == '\t' || *str == '\v' || *str == '\f'
		|| *str == '\r' || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		is_negative = (*str == '-');
		str++;
	}
	while (str[++i] >= '0' && str[i] <= '9')
		num = (num * 10) + str[i] - '0';
	if (is_negative)
		num = num * -1;
	return (num);
}
