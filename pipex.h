/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 02:42:47 by hugo-mar          #+#    #+#             */
/*   Updated: 2024/09/17 17:56:53 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_pipex_data
{
	int		argc;
	char	**argv;
	char	**envp;
	int		**pipes;
	int		nbr_pipes;
	int		labor_type;
	pid_t	*p_ids;
	int		exit_status;
}	t_pipex_data;

size_t	ft_strlen(const char *s);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strdup(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strjointwist(char *path, char *cmd);
char	*ft_strtrimtwist(char *s1, char const *set);
void	ft_free(char **argv);
char	**ft_split(char const *s, char c);
char	*path_search(char *command, char **envp);
void	freepipes(int **pipes, size_t nbr_of_pipes);
int		**pipemaker(int nbr_of_pipes);
void	parent_pipe_setup(t_pipex_data *data);
void	first_child_pipe_setup(int index, t_pipex_data *data);
void	middle_child_pipe_setup(int index, t_pipex_data *data);
void	last_child_pipe_setup(int index, t_pipex_data *data);
void	error_exit(t_pipex_data *data);
void	task_input_regular(int index, t_pipex_data *data);
void	task_input_here(int index, t_pipex_data *data);
void	task_command_execution(int index, t_pipex_data *data);
void	task_output_regular(int index, t_pipex_data *data);
void	task_output_here(int index, t_pipex_data *data);
void	work_assignment(int index, int class_type, t_pipex_data *data);
void	create_child(int index, int class_type, t_pipex_data *data);
void	child_labor(t_pipex_data *data);
void	wait_for_children(t_pipex_data *data);

#endif