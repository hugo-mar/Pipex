/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 03:20:02 by hugo-mar          #+#    #+#             */
/*   Updated: 2024/09/26 13:02:26 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(t_pipex_data *data, int pipe_fd)
{
	freepipes(data->pipes, data->nbr_pipes);
	free(data->p_ids);
	close(pipe_fd);
	exit(EXIT_FAILURE);
}

void	task_input_regular(int index, t_pipex_data *data)
{
	int		fd;
	char	buffer[1024];
	ssize_t	bytes_read;

	first_child_pipe_setup(index, data);
	fd = open (data->argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror(data->argv[1]);
		error_exit(data, data->pipes[index - 1][1]);
	}
	bytes_read = read(fd, buffer, sizeof(buffer));
	while (bytes_read > 0)
	{
		if (write(data->pipes[index - 1][1], buffer, bytes_read) == -1)
		{
			perror("write");
			close (fd);
			error_exit(data, data->pipes[index - 1][1]);
		}
		bytes_read = read(fd, buffer, sizeof(buffer));
	}
	close(data->pipes[index - 1][1]);
	close(fd);
}

void	task_input_here(int index, t_pipex_data *data)
{
	int		fd;
	char	buffer[BUFFER_SIZE];
	ssize_t	bytes_read;

	first_child_pipe_setup(index, data);
	fd = open("here_doc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	bytes_read = 0;
	while (1)
	{
		write(1, "> ", 2);
		bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
		if (bytes_read < 0)
		{
			perror("read");
			close(fd);
			error_exit(data, data->pipes[index - 1][1]);
		}
		buffer[bytes_read] = '\0';
		if (ft_strcmp(buffer, data->argv[2]) == '\n')
			break ;
		write(data->pipes[index - 1][1], buffer, bytes_read);
	}
	close(data->pipes[index - 1][1]);
	close (fd);
	unlink("here_doc");
}

void	task_command_execution(int index, t_pipex_data *data)
{
	char	**command;
	char	*path;

	middle_child_pipe_setup(index, data);
	dup2(data->pipes[index - 2][0], STDIN_FILENO);
	close(data->pipes[index - 2][0]);
	dup2(data->pipes[index - 1][1], STDOUT_FILENO);
	close(data->pipes[index - 1][1]);
	if (data->labor_type == 1)
		command = ft_split(data->argv[index + 1], ' ');
	else
		command = ft_split(data->argv[index], ' ');
	path = path_search(command[0], data->envp);
	execve(path, command, data->envp);
	if (execve(path, command, data->envp) == -1)
	{
		write(2, command[0], ft_strlen(command[0]));
		write(2, ": command not found\n", 20);
		free(path);
		ft_free(command);
		free(data->p_ids);
		freepipes(data->pipes, data->nbr_pipes);
		exit(127);
	}
}
