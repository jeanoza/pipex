/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 10:44:51 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/03/26 10:08:16 by kyubongchoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	validation_args(int ac, char **av)
{
	if (ac < 5)
	{
		write(1, "usage: ./pipex infile \"cmd1\" \"cmd2\" [cmd...] outfile\n", 53);
		exit (EXIT_FAILURE);
	}
	if (!(ft_strlen(av[2]) && ft_strlen(av[3])))
	{
		write(1, "Error: cmds can't be empty string\n", 34);
		exit (EXIT_FAILURE);
	}
	return (1);
}

static char	*find_path(char **env, char *cmd)
{
	int		i;
	char	**paths;
	char	*result;

	i = 0;
	while (env[i] && ft_strncmp("PATH=", env[i], 5))
		++i;
	if (env[i] == NULL)
		return (NULL);
	paths = ft_split(env[i] + 5, ':');
	result = NULL;
	i = -1;
	while (paths && paths[++i])
	{
		paths[i] = ft_strjoin_free_s1(paths[i], "/");
		paths[i] = ft_strjoin_free_s1(paths[i], cmd);
		if (access(paths[i], F_OK) == 0)
		{
			result = ft_strdup(paths[i]);
			break ;
		}
	}
	free_splitted(paths);
	return (result);
}

static void	execute(char *cmd, char **env)
{
	char	*path;
	char	**cmd_splitted;
	char	*cmd_error_msg;

	cmd_splitted = ft_split(cmd, ' ');
	path = find_path(env, cmd_splitted[0]);
	if (path)
		execve(path, cmd_splitted, env);
	else
	{
		free_splitted(cmd_splitted);
		cmd_error_msg = ft_strjoin_free_s1(
				ft_strjoin("zsh: command not found: ", cmd), "\n");
		write(STDERR_FILENO, cmd_error_msg, ft_strlen(cmd_error_msg));
		free(cmd_error_msg);
		exit(1);
	}
}

static void	redirection(int fd_in, char *cmd, char **env)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		perror_exit("pipe: ");
	pid = fork();
	if (pid == -1)
		perror_exit("fork: ");
	if (pid == 0)
	{
		close(pipe_fd[PIPE_READ]);
		dup2(pipe_fd[PIPE_WRITE], STDOUT_FILENO);
		if (fd_in == STDIN_FILENO)
			exit (1);
		else
			execute(cmd, env);
	}
	else
	{
		waitpid(-1, NULL, 0);
		close(pipe_fd[PIPE_WRITE]);
		dup2(pipe_fd[PIPE_READ], STDIN_FILENO);
	}
}

int	main(int ac, char **av, char **env)
{
	int	fd_in;
	int	fd_out;
	int	i;

	if (validation_args(ac, av))
	{
		fd_in = open(av[1], O_RDONLY);
		fd_out = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
		dup2(fd_in, STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		redirection(fd_in, av[2], env);
		i = 3;
		while (i < ac - 2)
			redirection(STDOUT_FILENO, av[i++], env);
		execute(av[i], env);
	}
	exit(EXIT_FAILURE);
}
