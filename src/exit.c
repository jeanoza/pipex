/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 15:32:49 by kychoi            #+#    #+#             */
/*   Updated: 2022/03/26 01:40:12 by kyubongchoi      ###   ########.fr       */
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

void	free_all(t_var *var)
{
	free_splitted(var->paths);
	free(var->shell);
	free(var);
}
