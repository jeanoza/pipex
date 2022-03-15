/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 10:44:51 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/03/15 08:46:28 by kyubongchoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(int fd, char *cmd, int *end)
{
	(void)cmd;

	//TODO: put protection if dup2() < 0
	printf("child1:%d\n", dup2(fd, STDIN_FILENO));
	printf("child2:%d\n", dup2(end[1], STDOUT_FILENO));
	// if (dup2(fd, STDIN_FILENO) < 0)
	// 	printf("error\n");
	// if (dup2(end[1], STDOUT_FILENO) < 0)
	// 	printf("error2\n");
	close(end[0]);
	close(fd);
	//execve....
	exit(1);
}

void	parent_process(int fd, char *cmd, int *end)
{
	int	status;

	(void)cmd;
	
	printf("exec in parent\n");

	waitpid(-1, &status, 0);

	printf("exec in parent2\n");
	dup2(fd, STDOUT_FILENO);
	dup2(end[0], STDIN_FILENO);
	close(end[1]);
	close(fd);
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
		return;
	}

	printf("fd1:%d fd2:%d\n", fd1, fd2);

	if (pid == 0) //if success fork(), operation in child process
	{
		//TODO: put protection if dup2() < 0
		printf("child:\n");
		if (dup2(fd1, STDIN_FILENO) < 0)
			printf("error\n");
		printf("child1\n");
		if (dup2(end[1], STDOUT_FILENO) < 0)
			printf("error2\n");
		printf("child2\n");
		close(end[0]);
		close(fd1);
		//execve....
		exit(1);
	}
	else {
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
	fd2 = open(av[1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	//0644 is permission bit 4=Read, 2=Write, 1=Execute
	if (fd1 < 0 || fd2 < 0)
		return (-1);
	pipex(fd1, fd2, av, env);
	return (0);
}
