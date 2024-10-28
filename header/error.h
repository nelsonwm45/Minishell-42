/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:30:56 by nchok             #+#    #+#             */
/*   Updated: 2024/10/28 11:31:40 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "./minishell.h"

/* Error Function */
void	free_array(char **arr);
int		clean_utils(t_env *utils);
int		error_message(int error_code, t_env *utils);

#endif