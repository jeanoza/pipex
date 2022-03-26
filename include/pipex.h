/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 10:43:10 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/03/26 02:55:04 by kyubongchoi      ###   ########.fr       */
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

void	free_splitted(char **splitted);
void	perror_exit(const char *msg);
char	**get_paths(char **env);

#endif
