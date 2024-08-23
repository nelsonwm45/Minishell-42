/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:09:49 by hheng             #+#    #+#             */
/*   Updated: 2024/07/03 08:44:00 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
#  define OPEN_MAX 256
# endif
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include "../libft.h"

char	*get_next_line(int fd);
int		line_len(char *buffer);
char	*set_line(char **left_over);
char	*ft_strjoin_special(char const *s1, char const *s2, int bytes_read);
char	*ft_strchr_gnl(const char *s, int c);
char	*ft_strdup_gnl(const char *s1);
void	fill_buffer(int fd, char *buffer, char **left_over);
#endif