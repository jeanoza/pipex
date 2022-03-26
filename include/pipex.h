/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 10:43:10 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/03/26 01:04:42 by kyubongchoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft.h"

# define PIPE_READ 0
# define PIPE_WRITE 1

/*
 * pipe_fd[0] : parent process - read
 * pipe_fd[1] : child process - write
 */
typedef struct s_var {
	int		ac;
	char	**env;
	char	**av;
	char	**paths;
	char	*shell;
}	t_var;

void	pipex(t_var *var);
void	free_all(t_var *var);
void	free_splitted(char **splitted);

#endif
