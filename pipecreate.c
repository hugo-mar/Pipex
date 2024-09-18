/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipecreate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 03:15:18 by hugo-mar          #+#    #+#             */
/*   Updated: 2024/09/14 03:16:47 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	freepipes(int **pipes, size_t nbr_of_pipes)
{
	size_t	i;

	i = 0;
	while (i < nbr_of_pipes)
		free(pipes[i++]);
	free(pipes);
}

static int	**allocatepipes(int nbr_of_pipes)
{
	int	**pipes;
	int	i;

	pipes = (int **) malloc (sizeof(int *) * nbr_of_pipes);
	if (!pipes)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < nbr_of_pipes)
	{
		pipes[i] = (int *) malloc (sizeof(int) * 2);
		if (!pipes[i])
		{
			freepipes(pipes, i);
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (pipes);
}

int	**pipemaker(int nbr_of_pipes)
{
	int	**pipes;
	int	i;

	pipes = allocatepipes(nbr_of_pipes);
	i = 0;
	while (i < nbr_of_pipes)
	{
		if (pipe(pipes[i]) == -1)
		{
			freepipes(pipes, nbr_of_pipes);
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (pipes);
}
