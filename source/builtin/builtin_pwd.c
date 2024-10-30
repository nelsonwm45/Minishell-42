/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng <hheng@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:45:14 by hheng             #+#    #+#             */
/*   Updated: 2024/10/30 13:45:14 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_pwd(void)
{
    char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        ft_putendl_fd(cwd, 1);
        return (SUCCESS);
    }
    else
    {
        perror("getcwd() error");
        return (ERROR);
    }
}


// int main(void)
// {
//     // Call the ft_pwd function
//     if (ft_pwd() == SUCCESS)
//     {
//         return 0;
//     }
//     else
//     {
//         return 1;
//     }
// }