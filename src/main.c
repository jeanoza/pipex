/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 10:44:51 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/03/26 02:00:37 by kyubongchoi      ###   ########.fr       */
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

static int	parsing(char **env, t_var *var)
{
	int		i;
	int		j;
	char	*path_from_env;

	i = -1;
	while (env && env[++i])
	{
		if (ft_strncmp("SHELL=", env[i], 6) == 0)
			var->shell = ft_substr(env[i], 11, ft_strlen(env[i]) - 11);
		if (ft_strncmp("PATH=", env[i], 5) == 0)
		{
			path_from_env = ft_substr(env[i], 5, ft_strlen(env[i]) - 5);
			var->paths = ft_split(path_from_env, ':');
			j = -1;
			while (var->paths && var->paths[++j])
				var->paths[j] = ft_strjoin_free_s1(var->paths[j], "/");
			free(path_from_env);
		}
	}
	if (var->shell && var->paths)
		return (1);
	return (0);
}

static void	execute(char *cmd, t_var *var)
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
		execve(cmd_with_path, cmd_av_splitted, var->env);
		free(cmd_with_path);
	}
	free_splitted(cmd_av_splitted);
	cmd_error_msg = ft_strjoin_free_s1(ft_strjoin(
				"zsh: command not found: ", cmd), "\n");
	write(STDERR_FILENO, cmd_error_msg, ft_strlen(cmd_error_msg));
	free(cmd_error_msg);
}

static void	redirection(int fd_in, t_var *var, int i)
{
	pid_t	pid;
	int		pipe_fd[2];

	//TODO:protection - perror && free_all(var)
	pipe(pipe_fd);
	//TODO:protection - perror && free_all(var)
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[PIPE_READ]);
		dup2(pipe_fd[PIPE_WRITE], STDOUT_FILENO);
		if (fd_in == STDIN_FILENO)
			exit (1);
		else
			execute(var->av[i], var);
	}
	else
	{
		waitpid(-1, NULL, 0);
		close(pipe_fd[PIPE_WRITE]);
		dup2(pipe_fd[PIPE_READ], STDIN_FILENO);
	}
}

// void	pipex(t_var *var, int ac, char **av, char **env)
void	pipex(t_var *var)
{
	int	fd_in;
	int	fd_out;
	int	i;

	fd_in = open(var->av[1], O_RDONLY);
	fd_out = open(var->av[var->ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	redirection(fd_in, var, 2);
	i = 3;
	while (i < var->ac - 2)
		redirection(STDOUT_FILENO, var, i++);
	execute(var->av[i], var);
}

int	main(int ac, char **av, char **env)
{
	t_var	*var;

	if (validation_args(ac, av))
	{
		var = malloc(sizeof(t_var));
		if (var == NULL)
			exit(EXIT_FAILURE);
		var->ac = ac;
		var->av = av;
		var->env = env;
		if (parsing(env, var) == 1)
			pipex(var);
		exit(EXIT_SUCCESS);
	}
}