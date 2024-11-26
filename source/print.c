/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchok <nchok@student.42kl..edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:27:37 by nchok             #+#    #+#             */
/*   Updated: 2024/11/26 17:16:24 by nchok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	print_cmds(t_cmds *cmds)
{
	t_cmds *ptr;
	int i;
	int count;

	ptr = cmds;
	count = 0;
	printf("------printing cmds------\n");
	while (ptr)
	{
		i = 0;
		printf("~~~~>>Node: %d\n", count);
		while (ptr->str[i])
		{
			printf("str: %s\n", ptr->str[i]);
			i++;
		}
		printf("builtin: %d\n", ptr->builtin);
		printf("redir_count: %d\n", ptr->redir_count);
		count++;
		ptr = ptr->next;
	}
}

void	print_lexer(t_lexer *lst)
{
	t_lexer *ptr;

	ptr = lst;
	printf("------printing lexer------\n");
	while (ptr)
	{
		printf("str: %s\n", ptr->str);
		printf("token_type: %d\n", ptr->token_type);
		ptr = ptr->next;
	}
}

int	print_envp(t_general *utils)
{
	int	i;

	i = 0;
	while (utils->envp[i])
	{
		ft_putstr_fd(utils->envp[i], 1);
		write(1, "\n", 1);
		i++;
	}
	return (0);
}