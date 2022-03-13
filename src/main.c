/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kychoi <kychoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 10:44:51 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/03/13 18:39:59 by kychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(int fd, char *cmd, int *end)
{
	(void)cmd;

	//TODO: put protection if dup2() < 0
	dup2(fd, STDIN_FILENO);
	printf("exec in child1\n");
	dup2(end[1], STDOUT_FILENO);
	printf("exec in child2\n");
	close(end[0]);
	printf("exec in child3\n");
	close(fd);
	//execve....
	printf("exec in child4\n");
	exit(1);
}

void	parent_process(int fd, char *cmd, int *end)
{
	int	status;

	(void)cmd;
	
	waitpid(-1, &status, 0);
	dup2(fd, STDOUT_FILENO);
	dup2(end[0], STDIN_FILENO);
	close(end[1]);
	close(fd);
	//execve....
	printf("exec in parent\n");
	exit(1);
}

/*
 * end[0] : parent process - read
 * end[1] : child process - write
 */
void	pipex(int fd1, int fd2, char **av, char **env)
{
	int		end[2];
	pid_t	parent;

	(void)env;

	pipe(end);
	parent = fork();
	if (parent == -1)
	{
		perror("Fork:");
		return;
	}
	if (parent == 0) //if success fork(), operation in child process
	{
		printf("child\n");
		child_process(fd1, av[2], end);
	}
	else
	{
		printf("parent\n");
		parent_process(fd2, av[3], end);
	}
}

int	main(int ac, char **av, char **env)
{
	int	fd1;
	int fd2;

	(void)ac;
	(void)av;
	(void)env;

	fd1 = open(av[1], O_RDONLY);
	// fd2 = open(av[1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	fd2 = open(av[4], O_CREAT | O_RDWR);
	printf("main before pipex\n");
	// if (fd1 < 0 || fd2 < 0)
	// 	return (-1);
	pipex(fd1, fd2, av, env);
	printf("main after pipex\n");
	return (0);
}
