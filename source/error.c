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

<<<<<<< HEAD
# include "../header/minishell.h"
=======
# include "minishell.h"
/*
	@brief
	- free the array
*/
void	free_array(char **arr)
{
	int	i;
>>>>>>> d9fd237 ( last fix)

int	double_token_error(t_general *utils, t_lexer *lexer, t_type token_type)
{
	ft_putstr_fd("Syntax error near unexpected token ", STDERR_FILENO);
	if (token_type == PIPE)
		ft_putstr_fd("'|'\n", STDERR_FILENO);
	else if (token_type == BIG)
		ft_putstr_fd("'>'\n", STDERR_FILENO);
	else if (token_type == BIGBIG)
		ft_putstr_fd("'>>'\n", STDERR_FILENO);
	else if (token_type == SMALL)
		ft_putstr_fd("'<'\n", STDERR_FILENO);
	else if (token_type == SMALLSMALL)
		ft_putstr_fd("'<'\n", STDERR_FILENO);
	clean_lexer(&lexer);
	clean_utils(utils);
	return (EXIT_FAILURE);
}

void	parsing_error(int error, t_general *utils, t_lexer *lexer)
{
	clean_lexer(&lexer);
	error_message(error, utils);
}
int	error_message(int error_code, t_general *utils)
{
	if (error_code == 1)
		ft_putstr_fd("Syntax error near unexpected token 'newline'\n", STDERR_FILENO);
	else if (error_code == 2)
		ft_putstr_fd("Syntax error: unable to locate closing quote\n", STDERR_FILENO);
	else if (error_code == 3)
		ft_putstr_fd("Parser Error\n", STDERR_FILENO);
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