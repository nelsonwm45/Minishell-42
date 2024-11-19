/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:21:06 by nchok             #+#    #+#             */
/*   Updated: 2024/11/14 18:21:06 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/*
** SIGINT: program interrupt signal (ctrl + C).
** SIGQUIT: (ctrl + \).
** EOT: end of transmission (ctrl + D).

130: Typically used to indicate a program was terminated by SIGINT.
131: Used to indicate termination by SIGQUIT.

** Case sig == 1: Handle parent(main) signal
	SIGINT (Ctrl + C) is handled by the restore_prompt function.
	SIGQUIT (Ctrl + \) is ignored using SIG_IGN.

** Case sig == 2: Handle child signal
	SIGINT is handled by the sig_init function.
	SIGQUIT is handled by the sig_quit function.

** Case sig == 3: for cleaning and termination purpose
	Prints "exit\n".
	Exits the program using exit(0).

*/

int g_ret_number = 0;

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
		signal(SIGQUIT, sig_quit);
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
	g_ret_number = 131;
	printf("quit\n");
	(void)sig;
}


