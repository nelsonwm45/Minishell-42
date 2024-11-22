/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:26:00 by nchok             #+#    #+#             */
/*   Updated: 2024/11/22 14:20:21 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	handle_cmd(t_general *utils, t_cmds *cmds)
{
	int	exit_code;

	exit_code = 0;
	if (cmds->redir)
		if (check_redir(cmds))
			exit(1);
	if (cmds->builtin != 0) // execute builtin here
	{
		exit_code = prep_builtin(utils, cmds, utils->mini);
		exit(exit_code);
	}
	else if (cmds->str[0][0] != '\0')
		exit_code = search_cmd(utils, cmds);
	exit(exit_code);
}

int	search_cmd(t_general *utils, t_cmds *cmds)
{
	int		i;
	char	*new_cmd;

	cmds->str = resplit_str(cmds->str);
	printf("cmds->str[0]: %s\n", cmds->str[0]);
	i = 0;
	if (!access(cmds->str[0], F_OK))
		execve(cmds->str[0], cmds->str, utils->envp);
	while (utils->path[i])
	{
		new_cmd = ft_strjoin(utils->path[i], cmds->str[0]);
		if (!access(new_cmd, F_OK))
			execve(new_cmd, cmds->str, utils->envp);
		free(new_cmd);
		i++;
	}
	return (cmd_not_found(cmds->str[0]));
}

