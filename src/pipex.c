/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kychoi <kychoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:20:12 by kychoi            #+#    #+#             */
/*   Updated: 2022/03/17 19:00:42 by kychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	execute(char *cmd, t_var *var)
{
	char	**cmd_av_splitted;
	char	*cmd_with_path;
	int		i;

	cmd_av_splitted = ft_split(cmd, ' ');
	i = -1;
	while (var->paths[++i])
	{
		cmd_with_path = ft_strjoin(var->paths[i], cmd_av_splitted[0]);
		//FIXME:programe finish juste after execve..
		//		=> How && when can I free the thing that i mallocated?
		execve(cmd_with_path, cmd_av_splitted, var->env);
		free(cmd_with_path);
	}
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
	exit(1);
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
	exit(1);
}

void	pipex(int fd1, int fd2, t_var *var)
{
	pid_t	pid;

	if (pipe(var->pipe_fd) == -1)
	{
		perror("pipe:");
		//TODO: free~
		exit(1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Fork:");
		//TODO: free~
		exit(1);
	}
	if (pid == 0)
		child_process(fd1, var);
	parent_process(fd2, var);
}
