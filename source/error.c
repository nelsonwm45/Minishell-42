/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:54:36 by nchok             #+#    #+#             */
/*   Updated: 2024/10/28 15:42:37 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"
/*
	@brief
	- free the array
*/
void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	clean_utils(t_general *utils)
{
	free_array(utils->envp);
	free_array(utils->path);
	free(utils->pwd);
	free(utils->oldpwd);
	free(utils->line);
	return (0);
}

int	error_message(int error_code, t_general *utils)
{
	if (error_code == 1)
		ft_putstr_fd("Syntax error near unexpected token 'newline'\n", STDERR_FILENO);
	else if (error_code == 2)
		ft_putstr_fd("Syntax error: unable to locate closing quote\n", STDERR_FILENO);
	clean_utils(utils);
	return (EXIT_FAILURE);
}

int error_message_path(char *path)
{
    DIR *folder;
    int fd;
    int ret;

    fd = open(path, O_WRONLY);
    folder = opendir(path);
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    ft_putstr_fd(path, STDERR_FILENO);
    if (ft_strchr(path, '/') == NULL)
        ft_putendl_fd(": command not found", STDERR_FILENO);
    else if (fd == -1 && folder == NULL)
        ft_putendl_fd(": No such file or directory", STDERR_FILENO);
    else if (fd == -1 && folder != NULL)
        ft_putendl_fd(": is a directory", STDERR_FILENO);
    else if (fd != -1 && folder == NULL)
        ft_putendl_fd(": Permission denied", STDERR_FILENO);
    if (ft_strchr(path, '/') == NULL || (fd == -1 && folder == NULL))
        ret = UNKNOWN_COMMAND;
    else
        ret = IS_DIRECTORY;
    if (folder)
        closedir(folder);
    ft_close(fd);
    return (ret);
}