/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:21:06 by nchok             #+#    #+#             */
/*   Updated: 2024/11/14 18:21:06 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/*
g_ret_number = global variable

** SIGINT: program interrupt signal (ctrl + C).
** SIGQUIT: (ctrl + \).
** EOT: end of transmission (ctrl + D).

	130: exit_status for SIGINT.
	131: exit_status for SIGQUIT.

** Case sig == 1: Handle parent(main) signal

** Case sig == 2: Handle child signal

** Case sig == 3: for cleaning and termination purpose

*/

int	g_ret_number = 0;

void	run_signals(int sig)
{
	if (sig == 1)
	{
		signal(SIGINT, restore_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == 2)
	{
		signal(SIGINT, sig_init);
		signal(SIGQUIT, SIG_DFL);
	}
	if (sig == 3)
	{
		printf("exit\n");
		exit(0);
	}
}

void	restore_prompt(int sig)
{
	g_ret_number = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

void	sig_init(int sig)
{
	g_ret_number = 130;
	write(1, "\n", 1);
	(void)sig;
}

void	sig_quit(int sig)
{
	write(1, "Quit (core dumped)\n", 19);
	(void)sig;
}
