/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 03:22:05 by hugo-mar          #+#    #+#             */
/*   Updated: 2024/09/17 15:05:27 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	open_output_file(char *file, int flags, t_pipex_data *data)
{
	int	fd;

	fd = open(file, flags, 0644);
	if (fd == -1)
	{
		perror(file);
		error_exit(data);
	}
	return (fd);
}

void	task_output_regular(int index, t_pipex_data *data)
{
	int		fd;
	int		i;
	char	buffer[1024];
	ssize_t	bytes_read;

	last_child_pipe_setup(index, data);
	i = 0;
	while (data->argv[i + 1])
		i++;
	fd = open_output_file(data->argv[i], O_WRONLY | O_CREAT | O_TRUNC, data);
	bytes_read = read(data->pipes[index - 2][0], buffer, sizeof(buffer));
	while (bytes_read > 0)
	{
		if (write(fd, buffer, bytes_read) == -1)
		{
			perror(data->argv[i]);
			error_exit(data);
		}
		bytes_read = read(data->pipes[index - 2][0], buffer, sizeof(buffer));
	}
	close(data->pipes[index - 2][0]);
	close(fd);
}

void	task_output_here(int index, t_pipex_data *data)
{
	int		fd;
	int		i;
	char	buffer[1024];
	ssize_t	bytes_read;

	last_child_pipe_setup(index, data);
	i = 0;
	while (data->argv[i + 1])
		i++;
	fd = open_output_file(data->argv[i], O_WRONLY | O_CREAT | O_APPEND, data);
	bytes_read = read(data->pipes[index - 2][0], buffer, sizeof(buffer));
	while (bytes_read > 0)
	{
		if (write(fd, buffer, bytes_read) == -1)
		{
			perror(data->argv[i]);
			error_exit(data);
		}
		bytes_read = read(data->pipes[index - 2][0], buffer, sizeof(buffer));
	}
	close(data->pipes[index - 2][0]);
	close(fd);
}
