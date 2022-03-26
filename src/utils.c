/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 15:32:49 by kychoi            #+#    #+#             */
/*   Updated: 2022/03/26 10:04:19 by kyubongchoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_splitted(char **splitted)
{
	int	i;

	i = -1;
	while (splitted && splitted[++i])
		free(splitted[i]);
	free(splitted);
}

void	perror_exit(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}
