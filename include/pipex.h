/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kychoi <kychoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 10:43:10 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/03/17 18:51:39 by kychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <fcntl.h>
# include "libft.h"

# define PIPE_READ 0
# define PIPE_WRITE 1

/*
 * pipe_fd[0] : parent process - read
 * pipe_fd[1] : child process - write
 */
typedef struct s_var {
	int		pipe_fd[2];
	int		cmd_idx;
	char	**env;
	char	**av;
	char	**paths;
}	t_var;

void	pipex(int fd1, int fd2, t_var *var);

#endif
