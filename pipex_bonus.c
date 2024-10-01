/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:16:45 by hugo-mar          #+#    #+#             */
/*   Updated: 2024/09/23 16:42:18 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	handle_few_args(int argc, char **argv)
{
	if (argc < 5)
		exit (EXIT_FAILURE);
	if (argc == 5)
	{
		if (ft_strcmp(argv[1], "here_doc") == 0)
			exit (EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex_data	data;

	if (argc <= 5)
		handle_few_args(argc, argv);
	data.argc = argc;
	data.argv = argv;
	data.envp = envp;
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		data.nbr_pipes = argc - 3;
		data.labor_type = 1;
	}
	else
	{
		data.nbr_pipes = argc - 2;
		data.labor_type = 0;
	}
	data.pipes = pipemaker(data.nbr_pipes);
	child_labor(&data);
	parent_pipe_setup(&data);
	wait_for_children(&data);
	freepipes(data.pipes, data.nbr_pipes);
	free(data.p_ids);
	return (data.exit_status);
}
