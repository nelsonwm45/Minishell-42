/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:25:36 by hheng             #+#    #+#             */
/*   Updated: 2024/07/03 08:54:05 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strjoin(char *s1, char *s2)
{
    char *str;
    int s1_len;
    int s2_len;

    // Handle the case where s1 is NULL by allocating an empty string
    if (!s1)
    {
        s1 = (char *)malloc(sizeof(char) * 1);
        if (!s1)
            return (NULL);
        s1[0] = '\0';
    }

    s1_len = ft_strlen(s1);
    s2_len = ft_strlen(s2);

    // Allocate memory for the new string (s1 + s2 + null terminator)
    str = (char *)malloc(s1_len + s2_len + 1);
    if (!str)
        return (NULL);

    // Copy the contents of s1 and s2 into the new string
    ft_memcpy(str, s1, s1_len);
    ft_memcpy(str + s1_len, s2, s2_len);
    str[s1_len + s2_len] = '\0';  // Null-terminate the new string

    // Free s1 if it was dynamically allocated (i.e., if s1 was originally NULL)
    if (s1[0] == '\0' && s1_len == 0)
        free(s1);

    return (str);
}