/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:44:45 by hheng             #+#    #+#             */
/*   Updated: 2024/10/30 13:44:45 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * This file implements the `echo` command for a shell.
 * 
 * The `echo` command writes its arguments to standard output.
 * If the first argument is "-n", it does not output the trailing newline.
 * 
 * The code replicates this functionality as follows:
 * - `nb_args`: Counts the number of arguments in the array.
 * - `ft_echo`: Main function to handle the `echo` command logic.
 *   - Checks for the "-n" option.
 *   - Prints each argument with a space separator.
 *   - Prints a newline if the "-n" option is not present.
 */

// Count the number of arguments in the array
static int nb_args(char **args) {
	int count = 0;
	while (args[count]) count++;
	return count;
}

// A simple echo implementation with support for the -n option
int ft_echo(char **args) {
	int i = 1;
	int n_option = 0;

	// Check for the "-n" option as the first argument
	if (nb_args(args) > 1 && ft_strcmp(args[1], "-n") == 0) {
		n_option = 1;
		i++; // Skip "-n" for the actual output
	}

	// Print each argument with a space separator
	while (args[i]) {
		ft_putstr_fd(args[i], 1);
		if (args[i + 1]) // Add a space if there are more arguments
			write(1, " ", 1);
		i++;
	}

	// Print a newline if -n option is not present
	if (!n_option)
		write(1, "\n", 1);

	return SUCCESS;
}
