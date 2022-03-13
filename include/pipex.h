/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kychoi <kychoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 10:43:10 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/03/13 17:48:45 by kychoi           ###   ########.fr       */
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

# define FDS_READ 0
# define FDS_WRITE 1

typedef struct s_var {
	int	end[2];

}	t_var;

#endif
