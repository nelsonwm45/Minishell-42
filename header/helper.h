/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:20:09 by nchok             #+#    #+#             */
/*   Updated: 2024/10/28 15:41:10 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPER_H
# define HELPER_H

# include <signal.h>

# include "./minishell.h"

void	init_signal(t_general *utils);
void	sigint_handler(int sig);

#endif