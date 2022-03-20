/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kychoi <kychoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 10:44:51 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/03/20 16:12:30 by kychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	validation_args(int ac, char **av)
{
	if (ac != 5)
	{
		write(1, "usage: ./pipex infile \"cmd1\" \"cmd2\" outfile\n", 44);
		exit (EXIT_FAILURE);
	}
	if (!(ft_strlen(av[2]) && ft_strlen(av[3])))
	{
		write(1, "Error: cmds can't be empty string\n", 34);
		exit (EXIT_FAILURE);
	}
}

static int	parsing(char **env, t_var *var)
{
	int		i;
	int		j;
	char	*path_from_env;

	i = -1;
	while (env && env[++i])
	{
		if (ft_strncmp("SHELL=", env[i], 6) == 0)
			var->shell = ft_substr(env[i], 11, ft_strlen(env[i]) - 11);
		if (ft_strncmp("PATH=", env[i], 5) == 0)
		{
			path_from_env = ft_substr(env[i], 5, ft_strlen(env[i]) - 5);
			var->paths = ft_split(path_from_env, ':');
			j = -1;
			while (var->paths && var->paths[++j])
				var->paths[j] = ft_strjoin_free_s1(var->paths[j], "/");
			free(path_from_env);
		}
	}
	if (var->shell && var->paths)
		return (1);
	return (0);
}

static int	init(int ac, char **av, char **env)
{
	t_var	*var;
	int		fd1;
	int		fd2;
	char	*err_msg;

	fd1 = open(av[1], O_RDONLY);
	if (fd1 == -1)
	{
		err_msg = ft_strjoin_free_s1(ft_strjoin(
					"zsh: no such file or directory:", av[1]), "\n");
		write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
		free(err_msg);
		exit(EXIT_FAILURE);
	}
	fd2 = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	var = malloc(sizeof(t_var));
	if (var == NULL)
		exit(EXIT_FAILURE);
	var->av = av;
	var->env = env;
	var->cmd_idx = 2;
	if (parsing(env, var) == 1)
		pipex(fd1, fd2, var);
	exit(EXIT_SUCCESS);
}


int	main(int ac, char **av, char **env)
{
	validation_args(ac, av);
	init(ac, av, env);
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