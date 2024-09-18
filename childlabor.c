/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childlabor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 03:23:24 by hugo-mar          #+#    #+#             */
/*   Updated: 2024/09/17 15:10:13 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	work_assignment(int index, int class_type, t_pipex_data *data)
{
	if (class_type == 1)
		task_input_regular(index, data);
	if (class_type == 2)
		task_input_here(index, data);
	if (class_type == 3)
		task_command_execution(index, data);
	if (class_type == 4)
		task_output_regular(index, data);
	if (class_type == 5)
		task_output_here(index, data);
}

void	create_child(int index, int class_type, t_pipex_data *data)
{
	pid_t	p_id;

	p_id = fork();
	if (p_id == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (p_id == 0)
	{
		work_assignment(index, class_type, data);
		freepipes(data->pipes, data->nbr_pipes);
		free(data->p_ids);
		exit(EXIT_SUCCESS);
	}
	if (p_id > 0)
	{
		data->p_ids[index - 1] = p_id;
	}
}

void	child_labor(t_pipex_data *data)
{
	int	i;

	data->p_ids = (pid_t *) malloc (sizeof(pid_t) * (data->nbr_pipes + 1));
	if (data->p_ids == NULL)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	i = 1;
	create_child(i++, 1 + data->labor_type, data);
	while ((i + data->labor_type) < (data->argc - 1))
	{
		create_child(i++, 3, data);
	}
	create_child(i, 4 + data->labor_type, data);
}

void	wait_for_children(t_pipex_data *data)
{
	int		status;
	int		exit_code;
	int		term_signal;
	int		i;

	i = 0;
	data->exit_status = 0;
	while (i < (data->nbr_pipes + 1))
	{
		if (waitpid(data->p_ids[i], &status, 0) != -1)
		{
			if (WIFEXITED(status))
			{
				exit_code = WEXITSTATUS(status);
				if (exit_code != 0)
					data->exit_status = exit_code;
			}
		}
		else if (WIFSIGNALED(status))
		{
			term_signal = WTERMSIG(status);
			data->exit_status = 128 + term_signal;
		}
		i++;
	}
}
