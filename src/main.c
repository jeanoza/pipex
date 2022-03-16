/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 10:44:51 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/03/16 09:18:48 by kyubongchoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//TODO:verify make file CFLAG

//FIXME: modify or create ft_strjoin with seperator
//to add "/" between path and cmd

void	execute(char *cmd, char **env)
{
	char	*path_from_env;
	char	**paths;
	char	**cmd_av_splitted;
	char	*new_cmd1;
	char	*new_cmd2;
	int		i;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			path_from_env = ft_substr(env[i], 5, ft_strlen(env[i]) - 5);
	}
	paths = ft_split(path_from_env, ':');
	cmd_av_splitted = ft_split(cmd, ' ');
	free(path_from_env);
	i = -1;
	while (paths[++i])
	{
		new_cmd1 = ft_strjoin(paths[i], "/");
		new_cmd2 = ft_strjoin(new_cmd1, cmd_av_splitted[0]);
		free(new_cmd1);
		if (execve(new_cmd2, cmd_av_splitted, env) == -1)
			perror("Error");
		free(new_cmd2);
	}
}

void	child_process(int fd1, char *cmd, int *end, char **av, char **env)
{
	(void)cmd;
	printf("(child) cmd:%s\n", cmd);
	if (dup2(fd1, STDIN_FILENO) < 0)
		perror("dup2(fd1, STDIN): ");
	if (dup2(end[1], STDOUT_FILENO) < 0)
		perror("dup2(end[1], STDOUT): ");
	close(end[0]);
	close(fd1);
	//execve....
	exit(1);
}

void	parent_process(int fd2, char *cmd, int *end, char **av, char **env)
{
	int	status;

	(void)cmd;

	printf("(parent) cmd:%s\n", cmd);
	waitpid(-1, &status, 0);

	if (dup2(fd2, STDOUT_FILENO) < 0)
		perror("dup2(fd, STDOUT_FILENO): ");
	if (dup2(end[0], STDIN_FILENO) < 0)
		perror("dup2(end[0], STDIN_FILENO): ");
	close(end[1]);
	close(fd2);
	//execve....
	exit(1);
}

/*
 * end[0] : parent process - read
 * end[1] : child process - write
 */
void	pipex(int fd1, int fd2, char **av, char **env)
{
	int		end[2];
	pid_t	pid;

	(void)env;

	pipe(end);
	pid = fork();
	if (pid == -1)
	{
		perror("Fork:");
		return ;
	}

	if (pid == 0) //if success fork(), operation in child process
		child_process(fd1, av[2], end, av, env);
	parent_process(fd2, av[3], end, av, env);
}


int	main(int ac, char **av, char **env)
{
	int	fd1;
	int fd2;

	(void)ac;
	(void)av;
	(void)env;

	execute("ls -al", env);


	fd1 = open(av[1], O_RDONLY);
	fd2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	//0644 is permission bit 4=Read, 2=Write, 1=Execute
	if (fd1 < 0 || fd2 < 0)
		return (-1);
	pipex(fd1, fd2, av, env);
	return (0);
}
