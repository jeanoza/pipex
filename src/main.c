/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 10:44:51 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/03/12 08:42:33 by kyubongchoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main()
{
	int pid1, pid2;
	pid1 = fork();
	if (pid1 == 0) {
		printf("[Child 1] : Hello, world ! pid=%d\n",getpid());
		exit(0);
	}
	pid2 = fork();
	if (pid2 == 0) {
		printf("[Child 2] : Hello, world ! pid=%d\n",getpid());
		exit(0);
	}
	else {
		printf("[Parent]: Hello, world ! pid=%d\n", getpid());
		exit(0);
	}

	//output called : [Parent] -> [Child 1] -> [Child 2]....
	// [Parent]: Hello, world ! pid=81955
	// [Child 1] : Hello, world ! pid=81956
	// [Child 2] : Hello, world ! pid=81957
}