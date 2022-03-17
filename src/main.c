/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kychoi <kychoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 10:44:51 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/03/17 18:53:43 by kychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//TODO:verify make file CFLAG
static int	parsing(char **av, char **env, t_var *var)
{
	int		i;
	int		j;
	char	*path_from_env;

	var->av = av;
	var->env = env;
	var->cmd_idx = 2;
	i = -1;
	while (env && env[++i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
		{
			path_from_env = ft_substr(env[i], 5, ft_strlen(env[i]) - 5);
			var->paths = ft_split(path_from_env, ':');
			j = -1;
			while (var->paths && var->paths[++j])
				var->paths[j] = ft_strjoin_free_s1(var->paths[j], "/");
			free(path_from_env);
			return (1);
		}
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_var	*var;
	int		fd1;
	int		fd2;

	//TODO:verify avs...
	if (ac < 5)
		exit (1);
	fd1 = open(av[1], O_RDONLY);
	fd2 = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	//TODO: find a way to manage if there is no fd1
	if (fd1 == -1 || fd2 == -1)
		return (-1);
	var = malloc(sizeof(t_var));
	if (var == NULL)
		exit(1);
	if (parsing(av, env, var) == 1)
		pipex(fd1, fd2, var);
	return (0);
}
//TODO: to put in free for paths
// for (int i = 0; var->paths[i]; ++i)
// {
// 	printf("%d:%s\n", i, var->paths[i]);
// 	free(var->paths[i]);
// }
// free(var->paths);
// free(var);

// #include <sys/wait.h>
// #include <assert.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <string.h>

// int main(int argc, char *argv[])
// {
//     int pipefd[2];
//     pid_t cpid;
//     char buf;

//     assert(argc == 2);

//     if (pipe(pipefd) == -1) {
//         perror("pipe");
//         exit(EXIT_FAILURE);
//     }

//     cpid = fork();
//     if (cpid == -1) {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     }

//     if (cpid == 0) {    /* Le fils lit dans le tube */
//         close(pipefd[1]);  /* Ferme l'extrémité d'écriture inutilisée */

//         while (read(pipefd[0], &buf, 1) > 0)
//             write(STDOUT_FILENO, &buf, 1);

//         write(STDOUT_FILENO, "\n", 1);
//         close(pipefd[0]);
//         _exit(EXIT_SUCCESS);

//     } else {                    /* Le père écrit argv[1] dans le tube */
//         close(pipefd[0]);       /* Ferme l'extrémité de lecture inutilisée */
//         write(pipefd[1], argv[1], strlen(argv[1]));
//         close(pipefd[1]);       /* Le lecteur verra EOF */
//         wait(NULL);             /* Attente du fils */
//         exit(EXIT_SUCCESS);
//     }
// }