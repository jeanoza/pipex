/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 15:32:49 by kychoi            #+#    #+#             */
/*   Updated: 2022/03/26 02:49:50 by kyubongchoi      ###   ########.fr       */
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

char	**get_paths(char **env)
{
	int		i;
	int		j;
	char	*path_from_env;
	char	**paths;

	i = -1;
	while (env && env[++i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
		{
			path_from_env = ft_substr(env[i], 5, ft_strlen(env[i]) - 5);
			paths = ft_split(path_from_env, ':');
			j = -1;
			while (paths && paths[++j])
				paths[j] = ft_strjoin_free_s1(paths[j], "/");
			free(path_from_env);
		}
	}
	return (paths);
}
