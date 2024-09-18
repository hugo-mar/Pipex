/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipesetup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 03:17:09 by hugo-mar          #+#    #+#             */
/*   Updated: 2024/09/14 03:18:52 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent_pipe_setup(t_pipex_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_pipes)
	{
		close(data->pipes[i][0]);
		close(data->pipes[i][1]);
		i++;
	}
}

void	first_child_pipe_setup(int index, t_pipex_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_pipes)
	{
		if (i != (index - 1))
			close(data->pipes[i][1]);
		close(data->pipes[i][0]);
		i++;
	}
}

void	middle_child_pipe_setup(int index, t_pipex_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_pipes)
	{
		if (i != (index - 2))
			close(data->pipes[i][0]);
		if (i != (index - 1))
			close(data->pipes[i][1]);
		i++;
	}
}

void	last_child_pipe_setup(int index, t_pipex_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_pipes)
	{
		if (i != (index - 2))
			close(data->pipes[i][0]);
		close(data->pipes[i][1]);
		i++;
	}
}
