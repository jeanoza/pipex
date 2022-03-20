/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kychoi <kychoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:20:12 by kychoi            #+#    #+#             */
/*   Updated: 2022/03/20 14:39:56 kychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	execute(const char *cmd, t_var *var)
{
	char	**cmd_av_splitted;
	char	*cmd_with_path;
	char	*cmd_error_msg;
	int		i;

	cmd_av_splitted = ft_split(cmd, ' ');
	i = -1;
	while (var->paths[++i])
	{
		cmd_with_path = ft_strjoin(var->paths[i], cmd_av_splitted[0]);
		if (execve(cmd_with_path, cmd_av_splitted, var->env) != -1)
		{
			free(cmd_with_path);
			free_splitted(cmd_av_splitted);
			return ;
		}
		free(cmd_with_path);
	}
	cmd_error_msg = ft_strjoin_free_s1(ft_strjoin_free_s1(ft_strjoin(
					var->shell, ": command not found: "), cmd), "\n");
	write(STDERR_FILENO, cmd_error_msg, ft_strlen(cmd_error_msg));
	free_splitted(cmd_av_splitted);
	free(cmd_error_msg);
	free_all(var);
}

static void	child_process(int fd1, t_var *var)
{
	if (dup2(fd1, STDIN_FILENO) < 0)
		perror("dup2(fd1, STDIN):");
	if (dup2(var->pipe_fd[PIPE_WRITE], STDOUT_FILENO) < 0)
		perror("dup2(pipe[1], STDOUT):");
	close(var->pipe_fd[PIPE_READ]);
	close(fd1);
	execute(var->av[var->cmd_idx], var);
	exit(EXIT_FAILURE);
}

static void	parent_process(int fd2, t_var *var)
{
	int	status;

	waitpid(-1, &status, 0);
	if (dup2(fd2, STDOUT_FILENO) < 0)
		perror("dup2(fd2, STDOUT):");
	if (dup2(var->pipe_fd[PIPE_READ], STDIN_FILENO) < 0)
		perror("dup2(pipe[0], STDIN):");
	close(var->pipe_fd[PIPE_WRITE]);
	close(fd2);
	execute(var->av[var->cmd_idx + 1], var);
	exit(EXIT_FAILURE);
}

void	pipex(int fd1, int fd2, t_var *var)
{
	pid_t	pid;

	if (pipe(var->pipe_fd) == -1)
	{
		perror("pipe:");
		free_all(var);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Fork:");
		free_all(var);
	}
	if (pid == 0)
		child_process(fd1, var);
	parent_process(fd2, var);
}
