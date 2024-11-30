/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheng < hheng@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:50:24 by hheng             #+#    #+#             */
/*   Updated: 2024/11/05 13:50:24 by hheng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i])
			ft_memdel(tab[i]);
		i++;
	}
	if (tab)
		ft_memdel(tab);
}

void	ft_putendl(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		i++;
	}
	write(1, "\n", 1);
}

char	*path_join(const char *s1, const char *s2)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin((char *)s1, "/");
	if (!tmp)
		return (NULL);
	path = ft_strjoin(tmp, (char *)s2);
	ft_memdel(tmp);
	return (path);
}

/*
1. Opens the directory specified by bin using opendir.
2. Loops through the directory entries (readdir) to check 
	if the command matches a file in the directory.
3. If found, constructs the full path using path_join.
4. Closes the directory with closedir.
5. Returns the full path if found; otherwise, returns NULL.
*/
char	*check_dir(char *bin, char *command)
{
	DIR				*folder;
	struct dirent	*item;
	char			*path;

	path = NULL;
	folder = opendir(bin);
	if (!folder)
		return (NULL);
	item = readdir(folder);
	while (item)
	{
		if (ft_strcmp(item->d_name, command) == 0)
			path = path_join(bin, item->d_name);
		item = readdir(folder);
	}
	closedir(folder);
	return (path);
}
/*
@brief : Processes the PATH environment variable into individual paths and 
			stores them in utils->path.

1. Loops through the path array, which contains parts of the PATH variable.
2. Ensures each path ends with a / by appending it if needed.
3. Removes the "PATH=" prefix from any entry that contains it.
4. Stores the processed paths into utils->path, ending the array with NULL.
*/

void	join_path(t_general *utils, char **path)
{
	int		i;
	char	*temp;

	i = 0;
	while (path[i])
	{
		if (path[i][ft_strlen(path[i]) - 1] != '/')
		{
			temp = path[i];
			path[i] = ft_strjoin(path[i], "/");
			free(temp);
		}
		if (ft_strncmp(path[i], "PATH=", 5) == 0)
			path[i] = ft_strtrim(path[i], "PATH=");
		utils->path[i] = path[i];
		i++;
	}
	utils->path[i] = NULL;
}
