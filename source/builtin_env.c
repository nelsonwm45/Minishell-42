#include "minishell.h"

/*
 * This file implements the `env` command for a shell.
 * 
 * The `env` command prints all the environment variables to the standard output.
 * Each environment variable is printed on a new line.
 * 
 * The code replicates this functionality as follows:
 * - `ft_env`: Main function to handle the `env` command logic.
 *   - Iterates through the linked list of environment variables.
 *   - Prints each environment variable's value.
 *   - Returns SUCCESS upon completion.
 */

int		ft_env(t_env *env)
{
	while (env && env->next != NULL)
	{
		ft_putendl_fd(env->value,1);
		env = env->next;
	}
	if (env)
		ft_putendl_fd(env->value, 1);
	return (SUCCESS);
}