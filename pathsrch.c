/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathsrch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 03:12:30 by hugo-mar          #+#    #+#             */
/*   Updated: 2024/09/17 15:09:21 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**get_paths(char **envp)
{
	char	**paths;
	int		i;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			paths = ft_split(envp[i], ':');
			paths[0] = ft_strtrimtwist(paths[0], "PATH=");
			return (paths);
		}
		i++;
	}
	return (NULL);
}

static char	*get_commandpath(char *command, char **paths)
{
	int		i;
	char	*commandpath;

	if (!command || !paths)
		return (NULL);
	i = 0;
	commandpath = NULL;
	while (paths[i])
	{
		paths[i] = ft_strjointwist(paths[i], command);
		if (access(paths[i], F_OK) != -1)
		{
			commandpath = ft_strdup(paths[i]);
			break ;
		}
		i++;
	}
	if (commandpath)
		return (commandpath);
	else
	{
		commandpath = ft_strdup(paths[0]);
		return (commandpath);
	}
}

char	*path_search(char *command, char **envp)
{
	char	**paths;
	char	*path;

	if (!command || command[0] == '\0')
		return (NULL);
	paths = get_paths(envp);
	path = get_commandpath(command, paths);
	if (paths)
		ft_free (paths);
	if (path)
		return (path);
	else
		return (NULL);
}
