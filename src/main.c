/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kychoi <kychoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 10:44:51 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/03/13 11:33:27 by kychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(void)
{
	int pid, child, status;
	
	printf("[%d] Parent start\n", getpid());
	pid = fork();
	if (pid == 0)
	{
		printf("[%d] Child start\n", getpid());
		exit(2);
	}

	child = wait(&status);
	printf("[%d] Child[%d(status:%d)] end\n", getpid(), child, status);
	printf("\tCode exit:%d\n", status >> 8);
}