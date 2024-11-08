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

static	int		nb_args(char **args)
{
	int		size;

	size = 0;
	while (args[size])
		size++;
	return (size);
}

int ft_echo(char **args)
{
    int i = 1;
    int n_option = 0;

    if (args == NULL || args[0] == NULL) // Check if args is NULL
        return -1; // Handle error or return early

    if (nb_args(args) > 1)
    {
        while (args[i] && ft_strcmp(args[i], "-n") == 0)
        {
            n_option = 1;
            i++;
        }

        while (args[i])
        {
            if (args[i] != NULL) {
                ft_putstr_fd(args[i], 1);
                if (args[i + 1] && args[i][0] != '\0')
                    write(1, " ", 1);
            }
            i++;
        }
    }
    if (n_option == 0)
        write(1, "\n", 1);
    return (SUCCESS);
}

// // Main function to test ft_echo
// int main(int ac, char **av)
// {
//     ft_echo(ac, av);
//     return 0;
// }

